// Defines all the things needed to make the program run such as randomizers, pausing systems, and flushing
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define PAUSE system("pause")
#define CLS system("cls")
#define SIZE 2222
#define FLUSH myFlush()

// Flushes everything out of the terminal except for our program
void myFlush();

// Creates a struct for all the dogs that will be in the race
typedef struct dog_struct
{
    // Name of dog
    char name[20];
    // Payout if the dog wins the race
    int payOut;
    // The percentage chance the dog actually wins
    int percentageWinning;
    // How many times the dog has won
    int dogWins;
} dog;

// Displays the main menu
void displayMenu()
{
    CLS;
    printf("**************************************\n");
    printf("**********Gambling Main Menu**********\n");
    printf("**************************************\n");
    printf("** G) Start a gamble and place your wager **\n");
    printf("** B) Checks your bank account **\n");
    printf("** R) Display the results of past races **\n");
    printf("** L) Leave the program **\n\n");
    printf("Enter your selection: ");
}

// Gets our choice and sets the result to a string
char getChoice()
{
    // This will change depending on our choice
    char result = ' ';
    // Displays the menu
    displayMenu();
    // Gives input for what our result will be
    scanf(" %c", &result); // This was recommended by chatGPT to add a space before %c to consume any leftover characters. This fixed an error that I had
    FLUSH;
    // Returns the result of our choice
    return result;
}

// Flushes everything out
void myFlush()
{
    while (getchar() != '\n')
        ;
} // end myFlush

// This displays the results of any race
void displayResults()
{
    CLS;
    printf("**************************************\n");
    printf("************Past Race Results*********\n");
    printf("**************************************\n");

    // Creates a file
    FILE *fp;
    // Opens said file
    fp = fopen("races.txt", "r");
    // If there is an error while opening the file...
    if (fp == NULL)
    {
        // Print out that there was an error and exits the function
        printf("Error opening file.\n");
        exit(1);
    }

    // Gets all our lines...
    char line[100];

    // This was from chatGPT because I couldn't figure out how to add lines of code to the "races.txt" file... Big credit for that
    while (fgets(line, 100, fp) != NULL)
    {
        printf("%s", line);
    }

    // Closes the file
    fclose(fp);

    // Allows a pause so we can actually read the results because beforehand it showed the results and then went right away to the displayMenu() function...
    PAUSE;
}

// Asks for a wager
int askWager()
{
    int wager;
    printf("Please specify how much are you willing to wager: ");
    // Stores our wager in the memory
    scanf("%d", &wager);
    FLUSH;
    // Returns an output like
    return wager;
}

// Allows us to pick a dog. This was incredibly difficult because I was still trying to learn pointers and didn't know I'd need them here :(
char *pickDog()
{
    // Allows us to choose a dog and then saves it
    char *dogChoose = malloc(20);
    printf("Here are the list of dogs to choose from and their chances of winning. Please type in the dog you want to bet on: ");
    scanf("%s", dogChoose);
    // Returns our chosen dog like always
    return dogChoose;
}

char chooseWithDrawOrDeposit()
{
    char choiceOne = ' ';
    scanf(" %c", &choiceOne);
    FLUSH;
    return choiceOne;
}

int main()
{

    // Once again opens the file. This is so that every time a race is done, it will update it for us. The printResults() function initalized it.
    FILE *fp;
    fp = fopen("races.txt", "a+");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    // Gives info to our dog struct
    dog dogName[20];
    dog pay;
    dog percent;
    dog wins;

    // This was long and tetious. I feel like there is any easy way to make this less complicated, but I got kinda lazy and couldn't figure it out without giving erros so this is all I have for now
    /*

        Just to give the basics of what this does, it stores each dog (because right each dog is in it's own "slot" in the array of dogs) and their individual names, payout, chances of winning, and how many times they've won. For example:

        dogName[0] gives the first dog and now I can give it's name, payout, etc. I had to use strcpy() because otherwise it gives errors. Thanks for chatGPT once again for helping me out with this :)

        Then all I had to do was grab the next dog in the array and repeat the process:

        dogName[1] grabs the next dog... and I just did that a bunch of time. Yay me :)

    */
    strcpy(dogName[0].name, "Jerry");
    dogName[0].payOut = 2;
    dogName[0].percentageWinning = 40;
    dogName[0].dogWins = 0;

    strcpy(dogName[1].name, "Josephine");
    dogName[1].payOut = 5;
    dogName[1].percentageWinning = 10;
    dogName[1].dogWins = 0;

    strcpy(dogName[2].name, "Poodles");
    dogName[2].payOut = 10;
    dogName[2].percentageWinning = 8;
    dogName[2].dogWins = 0;
    ;

    strcpy(dogName[3].name, "Doug");
    dogName[3].payOut = 15;
    dogName[3].percentageWinning = 6;
    dogName[3].dogWins = 0;
    ;

    strcpy(dogName[4].name, "Nim");
    dogName[4].payOut = 50;
    dogName[4].percentageWinning = 1;
    dogName[4].dogWins = 0;
    ;

    strcpy(dogName[5].name, "Horse");
    dogName[5].payOut = 20;
    dogName[5].percentageWinning = 4;
    dogName[5].dogWins = 0;
    ;

    strcpy(dogName[6].name, "Rocko");
    dogName[6].payOut = 10;
    dogName[6].percentageWinning = 8;
    dogName[6].dogWins = 0;
    ;

    strcpy(dogName[7].name, "Chip");
    dogName[7].payOut = 5;
    dogName[7].percentageWinning = 10;
    dogName[7].dogWins = 0;
    ;

    strcpy(dogName[8].name, "Winston");
    dogName[8].payOut = 3;
    dogName[8].percentageWinning = 13;
    dogName[8].dogWins = 0;
    ;

    // Makes the choice whatever the choice function returns
    char choice = ' ';

    // How much we wager when it returns in the wager function
    int wager;

    // And finally which dog we chose... for you guessed it... the dogChoose() function!!
    char *dogChoose;

    // This allows the person to choose whether or not they withdraw or deposit money
    int choiceAgain = ' ';

    // How much money you can gamble at first.
    float money = 100;

    // How much money you have in your savings.
    float savings = 100;

    // Creates a while loop that will continuously run while you don't choose L to leave the program
    while (choice != 'L')
    {
        // Gets your choice
        choice = getChoice();
        // If you choose to gamble...
        if (choice == 'G')
        {
            // Checks whether or not you can gamble BUT you can still gamble cause you have money in your savings still
            if (money <= 0)
            {
                printf("You have no money left to gamble. Go get some from your savings. You have $%.2f in your savings.\n", savings);
                PAUSE;
            }
            else
            {
                // Prints out how much money you have in your checkings account that way you don't accidently type in too much money.
                printf("You currently have $%.2f in your checkings account that you can use to wager. If you want to have more money in your checkings, go to you bank account and withdraw money from your savings.\n", money);

                // Asks for our wager
                wager = askWager();

                // Checks if you "accidently" wager more money than you have
                if (wager > money)
                {
                    printf("Sorry, but you don't have enough money to wager that amount. Try checking your bank account and try again.\n");
                    PAUSE;
                }
                // Checks if you wager $0 cause obviously you can't wager nothing
                else if (wager == 0)
                {
                    printf("I'm sorry, but you can't wager $0 into the race. Try again later.\n");
                    PAUSE;
                }
                // Otherwise begin the gamble
                else
                {
                    // Prints how much money you wagered
                    printf("You have wagered $%d into this race\n", wager);
                    money = money - wager;
                    // This prints out all the dogs so you can choose and it gives all the stats of each dog so you don't blindly choose
                    for (int i = 0; i < 9; i++)
                    {
                        printf("Dog: %s\tPayout %d times the wager\tOdds of Winning %d%%\n", dogName[i].name, dogName[i].payOut, dogName[i].percentageWinning);
                    }
                    // Checks if you choose a valid dog
                    int validChoice = 0;
                    while (!validChoice)
                    { // loop until a valid choice is made (you pick the correct dog)
                        validChoice = 0;
                        // Chooses a dog
                        dogChoose = pickDog();
                        for (int i = 0; i < 9; i++)
                        {
                            // Credit to chatGPT for this because there was an error I was getting where I couldn't compare the choice with the string so I had to do this so that way we can compare the dog to the string
                            if (strcmp(dogChoose, dogName[i].name) == 0)
                            {
                                printf("The dog you chose was %s and the odds of this dog winning is %d%%\n", dogChoose, dogName[i].percentageWinning);
                                validChoice = 1;

                                /*

                                    This is really hard to explain so I'm gonna try my best...

                                    Pretty much this sets a random number between 1 - 100 and that cooresponds with the percentage (percentage is 1 out of 100) and compares it to each dog's percentageWinnings by creating a for loop that loops through the dog's winningPercentage and then makes an if statemnt that say if the random number is less than the dog's percentage win, then it will be considered a win.

                                    For example, Jerry has a much greater chance (40%) because in order for Jerry win, the number could be anywhere from 1-40 (because it's less than his percentage winnings which is 40%). That means 40 out of 100 of the times of gambling, Jerry will win because like I said, the number can be anywhere from 1-40. In other words, in 40/100 races, Jerry will win, giving him that 40% chance of winning.

                                    Let's compare this to Horse who can only win if the randomNum is either 1-4. This means that Horse only has 4 chances of winning, or in other words, in 4/100 races, Horse will win, or a 4% chance of winning.

                                    Hopefully that makes sense and thanks for reading this long essay :)
                                */
                                int randomNum;
                                // Seed the random number generator with the current time
                                srand(time(NULL));

                                // Gives a random number from 1-100
                                randomNum = rand() % 100;

                                // If the random number is less than the percentage of the dog winning, you win!
                                if (randomNum <= dogName[i].percentageWinning)
                                {
                                    // Our winnings is whatever our wager was times the payOut
                                    float winnings = wager * dogName[i].payOut;
                                    printf("%s wins the race!  You got $%.2f back into your bank account.\n", dogName[i].name, winnings);
                                    // Adds the winnings to your checking account
                                    money = money + winnings;
                                    printf("You now have $%.2f added to your bank account. To access this, go to your bank account and withdraw the amount you want out of your savings.\n", money);
                                    PAUSE;
                                    // Resets everything and prints the results in the "races.txt" file
                                    choice = ' ';
                                    dogName[i].dogWins += 1;
                                    fprintf(fp, "Wager: $%d\tDog: %s\tPercentage of Winning: %d%%\tTimes won: %d\n", wager, dogChoose, dogName[i].percentageWinning, dogName[i].dogWins);
                                    fflush(fp);
                                    // fclose(fp);
                                }
                                // If you lose the race
                                else
                                {
                                    // Same as above....
                                    printf("%s loses the race.\n", dogName[i].name);
                                    printf("Better luck next time!\n");
                                    printf("You now have $%.2f in your spending account and $%.2f in your savings account.\n", money, savings);
                                    PAUSE;
                                    choice = ' ';
                                    fprintf(fp, "Wager: $%d\tDog: %s\tPercentage of Winning: %d%%\tTimes won: %d\n", wager, dogChoose, dogName[i].percentageWinning, dogName[i].dogWins);
                                    fflush(fp);
                                    // fclose(fp);
                                }
                            }
                        }
                        // If you don't give a valid dog then it will prompt you to list a dog again.
                        if (!validChoice)
                        {
                            printf("I'm sorry, but that's not a dog in the list. Please select a dog from the list provided\n");
                        }
                    }
                }
            }

            free(dogChoose); // free the memory allocated by pickDog()

            // If you lose all your money from gambling... then you can't gamble anymore and you have to restart :)
            if (money <= 0 && savings <= 0)
            {
                printf("Sorry, but you have no more money left to gamble. Go get a job or a ski mask and come back next week.");
                break;
            }
        }
        // If you choose B
        else if (choice == 'B')
        {
            printf("Right now you have $%.2f in your checking account and $%.2f in your savings account. Would you like to withdraw or deposit money (W/D): ", money, savings);

            // Chooses whether you want to withdraw or deposit money (same method as the menu choosing)
            choiceAgain = chooseWithDrawOrDeposit();

            // If you choose W
            if (choiceAgain == 'W')
            {
                int takeOut;
                printf("How much would you like to take out: ");
                scanf("%d", &takeOut);
                
                // If you try to take out more than you have... I'm watching you....
                if (takeOut > savings)
                {
                    printf("Sorry, but you don't have that much money to withdraw. Please try again later.\n");
                    PAUSE;
                }
                // Otherwise it works :thumbsup:
                else
                {
                    // Takes out money from the savings account
                    savings = savings - takeOut;
                    // Adds that into the checkings
                    money = money + takeOut;
                    printf("Awesome. You now have $%.2f in your checking account and $%.2f in your savings account.\n", money, savings);
                    choice = ' ';
                    PAUSE;
                }
            }
            // Does the opposite. Same code
            else if (choiceAgain == 'D')
            {
                int putIn;
                printf("How much money would you like put into your savings: ");
                scanf("%d", &putIn);

                if (putIn > money)
                {
                    printf("Sorry, you but don't have ethat much money to put into your savings. Please try again later.\n");
                    PAUSE;
                }
                else
                {
                    money = money - putIn;
                    savings = savings + putIn;
                    printf("Awesome. You now have $%.2f in your checking account and $%.2f in your savings account.\n", money, savings);
                    PAUSE;
                }
            }
        }
        // Prints the results... nice and simple
        else if (choice == 'R')
        {
            displayResults();
        }

        // Exits the program by breaking the loop
        else if (choice == 'L')
        {
            printf("Thank you for racing Greg. See ya next time :)");
            break;
        }
    }

    // Closes the file so nothing else gets added to the "races.txt" file.
    fclose(fp);

    return 0;
}
