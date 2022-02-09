package main

import (
	"bufio"
	"fmt"
	"log"
	"math/rand"
	"os"
	"strconv"
	"strings"
	"time"
)

type Question struct {
	text       string
	answerA    string
	answerB    string
	answerC    string
	answerD    string
	trueAnswer string
}

type Stat struct {
	questionsCount                 int
	correctAnswersCount            int
	wrongAnswersCount              int
	usedHintsCount                 int
	minWonPrizeWithoutDroppingOut  int
	maxWonPrizeWithoutDroppingOut  int
	countPlayersWithoutDroppingOut int
	allWonMoneyWithoutDroppingOut  int
	minDroppedPlayerPrize          int
	maxDroppedPlayerPrize          int
	countDropedPlayers             int
	allWonMoneyFromDroppedPlayers  int
}

var easyQuestions []Question
var mediumQuestions []Question
var hardQuestions []Question
var Statistic Stat

var easyQuestionsToken []Question
var mediumQuestionsToken []Question
var hardQuestionsToken []Question

var audience bool = true
var call bool = true
var fifty bool = true

func main() {
	readFile("easy.txt")
	readFile("medium.txt")
	readFile("hard.txt")
	readStatistic("statistic.txt")

	var answer string

	for answer != "quit" {
		fmt.Println("Input (play/quit/addQuestion/printStatistic/resetStatistic)")
		fmt.Scanf("%s", &answer) //this just ignore the previous string
		fmt.Scanf("%s", &answer)

		if answer == "play" {
			playGame()
		} else if answer == "addQuestion" {
			addQuestion()
		} else if answer == "printStatistic" {
			printStatistic()
		} else if answer == "resetStatistic" {
			resetStatistic()
		}
	}

	//fmt.Println(easyQuestions)
	//fmt.Println(mediumQuestions)
	//fmt.Println(hardQuestions)

	saveFile("easy.txt")
	saveFile("medium.txt")
	saveFile("hard.txt")
	saveStatistic("statistic.txt")
}

func readFile(fileName string) {
	var line int = 1
	var current Question
	f, err := os.Open(fileName)

	if err != nil {
		fmt.Println("Problem with file")
		log.Fatal(err)
	}

	defer f.Close()

	scanner := bufio.NewScanner(f)

	for scanner.Scan() {
		var result string = strings.Trim(scanner.Text(), " ")

		if line == 1 {
			current.text = result
		} else if line == 2 {
			current.answerA = result
		} else if line == 3 {
			current.answerB = result
		} else if line == 4 {
			current.answerC = result
		} else if line == 5 {
			current.answerD = result
		} else {
			current.trueAnswer = result
		}

		if fileName == "easy.txt" && line == 6 {
			easyQuestions = append(easyQuestions, current)
		} else if fileName == "medium.txt" && line == 6 {
			mediumQuestions = append(mediumQuestions, current)
		} else if fileName == "hard.txt" && line == 6 {
			hardQuestions = append(hardQuestions, current)
		}

		if line == 6 {
			line = 0
		}
		line++
	}

	if err := scanner.Err(); err != nil {
		fmt.Println("Problem with file")
		log.Fatal(err)
	}
}

func saveFile(fileName string) {
	var current []Question
	f, err := os.Create(fileName)

	if err != nil {
		fmt.Println("Problem with file")
		log.Fatal(err)
	}

	defer f.Close()

	if fileName == "easy.txt" {
		current = easyQuestions
	} else if fileName == "medium.txt" {
		current = mediumQuestions
	} else if fileName == "hard.txt" {
		current = hardQuestions
	}

	for i := 0; i < len(current); i++ {
		f.WriteString(current[i].text + "\n")
		f.WriteString(current[i].answerA + "\n")
		f.WriteString(current[i].answerB + "\n")
		f.WriteString(current[i].answerC + "\n")
		f.WriteString(current[i].answerD + "\n")
		f.WriteString(current[i].trueAnswer + "\n")
	}
}

func playGame() {
	var question int = 1
	var isLive bool = true
	var minSum int = 0

	//easyQuestionsToken := make([]Question, len(easyQuestions))
	//mediumQuestionsToken := make([]Question, len(mediumQuestions))
	//hardQuestionsToken := make([]Question, len(hardQuestions))
	//copy(easyQuestionsToken, easyQuestions)
	//copy(mediumQuestionsToken, mediumQuestions)
	//copy(hardQuestionsToken, hardQuestions)
	easyQuestionsToken = append([]Question(nil), easyQuestions...)
	mediumQuestionsToken = append([]Question(nil), mediumQuestions...)
	hardQuestionsToken = append([]Question(nil), hardQuestions...)

	fmt.Println(easyQuestionsToken)
	//easyQuestionsToken = append(easyQuestions)
	//mediumQuestionsToken = append(mediumQuestions)
	//hardQuestionsToken = append(hardQuestions)
	audience = true
	call = true
	fifty = true

	for isLive {
		isLive = playCurrentQuestionGame(&question)

		if question == 4 {
			minSum = 500
		} else if question == 7 {
			minSum = 2500
		}
	}

	if question == 0 {
		fmt.Println("You won ", minSum)

		Statistic.allWonMoneyFromDroppedPlayers += minSum
		Statistic.countDropedPlayers += 1

		if Statistic.maxDroppedPlayerPrize < minSum {
			Statistic.maxDroppedPlayerPrize = minSum
		}
		if Statistic.minDroppedPlayerPrize > minSum {
			Statistic.minDroppedPlayerPrize = minSum
		}
	} else {
		calcSum(question)

		Statistic.allWonMoneyWithoutDroppingOut += minSum
		Statistic.countPlayersWithoutDroppingOut += 1

		if Statistic.maxWonPrizeWithoutDroppingOut < minSum {
			Statistic.maxWonPrizeWithoutDroppingOut = minSum
		}
		if Statistic.minWonPrizeWithoutDroppingOut > minSum {
			Statistic.minWonPrizeWithoutDroppingOut = minSum
		}
	}
}

func playCurrentQuestionGame(currentQuestion *int) bool {
	fmt.Println("Question number ", *currentQuestion)

	rand.Seed(time.Now().UnixNano())
	var index int
	var question Question

	if *currentQuestion <= 3 {
		index = rand.Intn(len(easyQuestionsToken))
		question = easyQuestionsToken[index]
		easyQuestionsToken = RemoveIndex(easyQuestionsToken, index)

	} else if *currentQuestion <= 6 {
		index = rand.Intn(len(mediumQuestionsToken))
		question = mediumQuestionsToken[index]
		mediumQuestionsToken = RemoveIndex(mediumQuestionsToken, index)
	} else {
		index = rand.Intn(len(hardQuestionsToken))
		question = hardQuestionsToken[index]
		hardQuestionsToken = RemoveIndex(hardQuestionsToken, index)
	}

	printQuestion(question)

	var answer string

	for *currentQuestion != 0 {
		fmt.Scanf("%s", &answer) //this just ignore the previous string
		fmt.Scanf("%s", &answer)

		if answer == "pass" {
			return false
		} else if answer == "fifty" {
			if fifty {
				printFifty(question)
			} else {
				fmt.Println("You already use fifty")
			}

		} else if answer == "audience" {
			if audience {
				printAudience(question)
			} else {
				fmt.Println("You already use audence")
			}

		} else if answer == "call" {
			if call {
				printCall(question)
			} else {
				fmt.Println("You already use call")
			}
		} else if answer == question.trueAnswer {
			fmt.Println("The answer is correct")
			*currentQuestion += 1
			Statistic.correctAnswersCount += 1
			if *currentQuestion == 10 {
				return false
			}

			return true
		} else if answer == "a" || answer == "b" || answer == "c" || answer == "d" {
			*currentQuestion = 0
		} else {
			fmt.Println("Invalid answer. Please try again")
		}
	}

	fmt.Println("Your answer is wrong")
	Statistic.wrongAnswersCount += 1
	return false
}

func printQuestion(question Question) {
	fmt.Println(question.text)
	fmt.Println("A: ", question.answerA)
	fmt.Println("B: ", question.answerB)
	fmt.Println("C: ", question.answerC)
	fmt.Println("D:", question.answerD)
	fmt.Println("Who is the correct answer (Write a/b/c/d/pass/fifty/call/audience)")

	Statistic.questionsCount += 1
}

func calcSum(question int) {
	if question == 1 {
		fmt.Println("You won ", 0)
	} else if question == 2 {
		fmt.Println("You won ", 100)
	} else if question == 3 {
		fmt.Println("You won ", 250)
	} else if question == 4 {
		fmt.Println("You won ", 500)
	} else if question == 5 {
		fmt.Println("You won ", 1000)
	} else if question == 6 {
		fmt.Println("You won ", 1500)
	} else if question == 7 {
		fmt.Println("You won ", 2500)
	} else if question == 8 {
		fmt.Println("You won ", 5000)
	} else if question == 9 {
		fmt.Println("You won ", 10000)
	} else {
		fmt.Println("You won ", 50000)
	}
}

func RemoveIndex(s []Question, index int) []Question {
	return append(s[:index], s[index+1:]...)
}

func printFifty(question Question) {
	rand.Seed(time.Now().UnixNano())

	var num1, num2 int

	num1 = AnswToNum(question.trueAnswer)
	for {
		num2 = rand.Intn(4) + 1

		if num2 != num1 {
			break
		}
	}

	var otherAnsw string = NumToAnswer(num2)

	if num1 < num2 {
		fmt.Println(question.trueAnswer)
		fmt.Println(otherAnsw)
	} else {
		fmt.Println(otherAnsw)
		fmt.Println(question.trueAnswer)
	}

	Statistic.usedHintsCount += 1
	fifty = false
}

func printAudience(question Question) {
	rand.Seed(time.Now().UnixNano())

	var num1 int = rand.Intn(71) + 30
	var num2 int = rand.Intn(100 - (num1 + 1))
	var num3 int = rand.Intn(100 - (num1 + num2 + 1))
	var num4 int = 100 - (num1 + num2 + num3)

	if "a" == question.trueAnswer {
		fmt.Println("a ", num1, "%")
		fmt.Println("b ", num2, "%")
		fmt.Println("c ", num3, "%")
		fmt.Println("d ", num4, "%")
	} else if "b" == question.trueAnswer {
		fmt.Println("a ", num2, "%")
		fmt.Println("b ", num1, "%")
		fmt.Println("c ", num3, "%")
		fmt.Println("d ", num4, "%")
	} else if "c" == question.trueAnswer {
		fmt.Println("a ", num3, "%")
		fmt.Println("b ", num2, "%")
		fmt.Println("c ", num1, "%")
		fmt.Println("d ", num4, "%")
	} else {
		fmt.Println("a ", num4, "%")
		fmt.Println("b ", num2, "%")
		fmt.Println("c ", num3, "%")
		fmt.Println("d ", num1, "%")
	}
	Statistic.usedHintsCount += 1
	audience = false
}
func printCall(question Question) {
	rand.Seed(time.Now().UnixNano())
	var num int = rand.Intn(100)

	if num < 30 {
		fmt.Println("I don't know the answer")
	} else if num < 70 {
		num = rand.Intn(4) + 1
		var answer string = NumToAnswer(num)
		fmt.Println("I think that the answer is ", answer)

	} else {
		fmt.Println("I am sure. The answer is ", question.trueAnswer)
	}

	Statistic.usedHintsCount += 1
	call = false
}

func NumToAnswer(num int) string {
	if num == 1 {
		return "a"
	} else if num == 2 {
		return "b"
	} else if num == 3 {
		return "c"
	} else {
		return "d"
	}
}

func AnswToNum(answ string) int {
	if answ == "a" {
		return 1
	} else if answ == "b" {
		return 2
	} else if answ == "c" {
		return 3
	} else {
		return 4
	}
}

func addQuestion() {
	var currentQuestion Question
	var input string = ""

	fmt.Println("Input question text")
	currentQuestion.text = readFromConsole()

	fmt.Println("Input answer a")
	currentQuestion.answerA = readFromConsole()

	fmt.Println("Input answer b")
	currentQuestion.answerB = readFromConsole()

	fmt.Println("Input answer c")
	currentQuestion.answerC = readFromConsole()

	fmt.Println("Input answer d")
	currentQuestion.answerD = readFromConsole()

	for input != "a" && input != "b" && input != "c" && input != "d" {
		fmt.Println("Which is the true answer (a/b/c/d)")
		input = readFromConsole()
	}
	currentQuestion.trueAnswer = input

	for input != "easy" && input != "hard" && input != "medium" {
		fmt.Println("What is the question's level (easy/medium/hard)")
		input = readFromConsole()
	}

	if input == "easy" {
		easyQuestions = append(easyQuestions, currentQuestion)
	} else if input == "medium" {
		mediumQuestions = append(mediumQuestions, currentQuestion)
	} else if input == "hard" {
		hardQuestions = append(hardQuestions, currentQuestion)
	}

	//fmt.Println(easyQuestions)
	//fmt.Println(mediumQuestions)
	//fmt.Println(hardQuestions)
}

func readFromConsole() string {
	reader := bufio.NewReader(os.Stdin)
	input, _ := reader.ReadString('\n')
	input = strings.Replace(input, "\n", "", -1)
	input = input[:len(input)-1]
	return input
}

func printStatistic() {
	fmt.Println("Statistic")
	fmt.Println("Questions count: ", Statistic.questionsCount)
	fmt.Println("Correct answer count: ", Statistic.correctAnswersCount)
	fmt.Println("Wrong answer count: ", Statistic.wrongAnswersCount)
	fmt.Println("Used hints count: ", Statistic.usedHintsCount)

	//Print Min Prize for player without dropping out
	if Statistic.minWonPrizeWithoutDroppingOut == 10000000 {
		fmt.Println("Min won Prize without dropping out: ", 0)
	} else {
		fmt.Println("Min won Prize without dropping out: ", Statistic.minWonPrizeWithoutDroppingOut)
	}

	//Print average Prize for players who have not been eliminated
	if Statistic.countPlayersWithoutDroppingOut == 0 {
		fmt.Println("Average won Prize without dropping out: ", 0)
	} else {
		fmt.Println("Average won Prize without dropping out: ", Statistic.allWonMoneyFromDroppedPlayers/Statistic.countPlayersWithoutDroppingOut)
	}

	fmt.Println("Max won Prize without dropping out: ", Statistic.maxWonPrizeWithoutDroppingOut)

	//Print Min Prize for playerwho has dropped out
	if Statistic.minDroppedPlayerPrize == 10000000 {
		fmt.Println("Min won Prize for a player who has dropped out: ", 0)
	} else {
		fmt.Println("Min won Prize for a player who has dropped out: ", Statistic.minDroppedPlayerPrize)
	}

	//Print average Prize for players who have dropped out
	if Statistic.countDropedPlayers == 0 {
		fmt.Println("Average won Prize for a player who has dropped out: ", 0)

	} else {
		fmt.Println("Average won Prize for a player who has dropped out: ", Statistic.allWonMoneyFromDroppedPlayers/Statistic.countDropedPlayers)
	}

	fmt.Println("Max won Prize for a player who has dropped out: ", Statistic.maxDroppedPlayerPrize)
}

func readStatistic(fileName string) {
	var current Stat
	f, err := os.Open(fileName)

	if err != nil {
		fmt.Println("in")
		//log.Fatal(err)
		current.questionsCount = 0
		current.correctAnswersCount = 0
		current.wrongAnswersCount = 0
		current.usedHintsCount = 0
		current.countPlayersWithoutDroppingOut = 0
		current.allWonMoneyWithoutDroppingOut = 0
		current.maxWonPrizeWithoutDroppingOut = 0
		current.minWonPrizeWithoutDroppingOut = 10000000
		current.countDropedPlayers = 0
		current.allWonMoneyFromDroppedPlayers = 0
		current.minDroppedPlayerPrize = 10000000
		current.maxDroppedPlayerPrize = 0

		Statistic = current
		return
	}

	defer f.Close()
	var index int = 0
	scanner := bufio.NewScanner(f)

	for scanner.Scan() {

		if index == 0 {
			current.questionsCount, _ = strconv.Atoi(strings.Trim(scanner.Text(), " "))
		} else if index == 1 {
			current.correctAnswersCount, _ = strconv.Atoi(strings.Trim(scanner.Text(), " "))
		} else if index == 2 {
			current.wrongAnswersCount, _ = strconv.Atoi(strings.Trim(scanner.Text(), " "))
		} else if index == 3 {
			current.usedHintsCount, _ = strconv.Atoi(strings.Trim(scanner.Text(), " "))
		} else if index == 4 {
			current.countPlayersWithoutDroppingOut, _ = strconv.Atoi(strings.Trim(scanner.Text(), " "))
		} else if index == 5 {
			current.allWonMoneyWithoutDroppingOut, _ = strconv.Atoi(strings.Trim(scanner.Text(), " "))
		} else if index == 6 {
			current.maxWonPrizeWithoutDroppingOut, _ = strconv.Atoi(strings.Trim(scanner.Text(), " "))
		} else if index == 7 {
			current.minWonPrizeWithoutDroppingOut, _ = strconv.Atoi(strings.Trim(scanner.Text(), " "))
		} else if index == 8 {
			current.countDropedPlayers, _ = strconv.Atoi(strings.Trim(scanner.Text(), " "))
		} else if index == 9 {
			current.allWonMoneyFromDroppedPlayers, _ = strconv.Atoi(strings.Trim(scanner.Text(), " "))
		} else if index == 10 {
			current.minDroppedPlayerPrize, _ = strconv.Atoi(strings.Trim(scanner.Text(), " "))
		} else if index == 11 {
			current.maxDroppedPlayerPrize, _ = strconv.Atoi(strings.Trim(scanner.Text(), " "))
		}
		index += 1

	}
	Statistic = current
}

func resetStatistic() {
	Statistic.questionsCount = 0
	Statistic.correctAnswersCount = 0
	Statistic.wrongAnswersCount = 0
	Statistic.usedHintsCount = 0
	Statistic.countPlayersWithoutDroppingOut = 0
	Statistic.allWonMoneyWithoutDroppingOut = 0
	Statistic.maxWonPrizeWithoutDroppingOut = 0
	Statistic.minWonPrizeWithoutDroppingOut = 10000000
	Statistic.countDropedPlayers = 0
	Statistic.allWonMoneyFromDroppedPlayers = 0
	Statistic.minDroppedPlayerPrize = 10000000
	Statistic.maxDroppedPlayerPrize = 0

	fmt.Println("Stats are reseted")
}

func saveStatistic(fileName string) {
	f, err := os.Create(fileName)

	if err != nil {
		fmt.Println("Problem with file")
		log.Fatal(err)
	}

	defer f.Close()

	f.WriteString(strconv.Itoa(Statistic.questionsCount) + "\n")
	f.WriteString(strconv.Itoa(Statistic.correctAnswersCount) + "\n")
	f.WriteString(strconv.Itoa(Statistic.wrongAnswersCount) + "\n")
	f.WriteString(strconv.Itoa(Statistic.usedHintsCount) + "\n")
	f.WriteString(strconv.Itoa(Statistic.countPlayersWithoutDroppingOut) + "\n")
	f.WriteString(strconv.Itoa(Statistic.allWonMoneyWithoutDroppingOut) + "\n")
	f.WriteString(strconv.Itoa(Statistic.maxWonPrizeWithoutDroppingOut) + "\n")
	f.WriteString(strconv.Itoa(Statistic.minWonPrizeWithoutDroppingOut) + "\n")
	f.WriteString(strconv.Itoa(Statistic.countDropedPlayers) + "\n")
	f.WriteString(strconv.Itoa(Statistic.allWonMoneyFromDroppedPlayers) + "\n")
	f.WriteString(strconv.Itoa(Statistic.maxDroppedPlayerPrize) + "\n")
	f.WriteString(strconv.Itoa(Statistic.minDroppedPlayerPrize) + "\n")
}
