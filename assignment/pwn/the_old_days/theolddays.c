// gcc -fno-stack-protector -no-pie theolddays.c -o theolddays
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <signal.h>

int decide();
void wait();
bool call();
void hesitate();
void leave();
void check_credit();
void deduct_processing_fee(bool);
void give_extra_feature();
void invalid_decision();
int read_int();
void timeout();

// variables
unsigned char credit_available = 30;
char hidden_access_input[32];
char call_content[64];


// Code to disable IO buffering
void setup()
{
    setvbuf(stdin, 0LL, 2, 0LL);
    setvbuf(stdout, 0LL, 2, 0LL);
    setvbuf(stderr, 0LL, 2, 0LL);

    signal(SIGALRM, timeout);           // Set program to exit on timeout
    alarm(40);                          // Exit program after 10s
}

void banner(){
    // Copyright of LGB from ASCII Art (https://ascii.co.uk/art/phonebooth)
    puts("     _.------._ ");   
    puts(" _.-'          '-._ ");   
    puts("/                  \\"); 
    puts("'------------------'");
    puts("| .--------------. |");
    puts("| |      ||      | |");
    puts("|[]      ||      | |");
    puts("| |======||======| |");
    puts("| |      ||      | |");
    puts("| |      ||      | |");
    puts("|[]======||======[ |");
    puts("| |======||======| |");
    puts("| |      ||      | |");
    puts("| |      ||      | |");
    puts("|[]======||======| |");
    puts("| |      ||      | |");
    puts("| '------''------' |");
    puts("|__________________|");
    puts("Photobooth is crowded with people. Better keep your messages short!");
    puts("");
}

int decide(){
    printf("\n==================\n");
    printf("Let's see how much time you've got: %d\n", credit_available);
    printf("1) Wait\n");
    printf("2) Call\n");
    printf("3) Hesitate\n");
    printf("4) Leave\n");
    printf("==================\n");
    printf("Make a decision: \n");
    printf("> ");
    return read_int();
}

void wait(){
    printf("You decided to wait. But how long?\n");
    printf("> ");
    int time_to_wait = read_int();
    credit_available+=time_to_wait;
    printf("You waited...\n");
}

bool call(){
    char message[100];
    int message_length;
    printf("You picked up the phone. What do you wish to say?\n");
    printf("Time is money. 1 credit = 1 char\n");
    printf("You have %d credits\n", credit_available);
    printf("> ");
    fgets(message, credit_available, stdin);

    strncpy(call_content, message, strlen(message));

    message_length = strlen(message) - 1;
    if(message_length == 0){
        printf("How can you pick up the phone and say nothing!\n");
        return false;
    }
    credit_available-=message_length;
    printf("Thanks for calling! You have %d credits left\n", credit_available);
    return true;
}

void hesitate(){
    printf("You hesitated\n");
    printf("Seems like your time is not limited, eh?\n");
}

void leave(){
    printf("It is taking too long!!!\n");
    printf("I'm gonna leave...\n");
    exit(0);
}

void check_credit(){
    if(credit_available > 50){
        int deduct_amount;
        deduct_amount = rand() % 20 + 30;
        credit_available = deduct_amount;
        printf("You have more than enough credit. Can't let you hog the phone\n");
        printf("Distributed your credits. You now have %d. Fair for everyone\n\n", credit_available);
    }
    else if(credit_available < 0){
        int deduct_amount;
        deduct_amount = rand() % 20 + 30;
        printf("Hey hey hey! No playing tricks here\n");
        printf("Resetting your credits to %d. Don't do that again\n", credit_available);
    }
}

void deduct_processing_fee(bool deduct){
    if(deduct){
        credit_available-=1;
        printf("You took one credit to decide. Deduct 1 credit\n");
        return;
    }
}

void give_extra_feature(){
    printf("Before you end the call, the phone operator says: \n");
    system("cat ./flag.txt");
}

void invalid_decision(){
    printf("Hey be a nice citizen! Don't waste time!\n");
}

int read_int(){
    char choice[8];
    fgets(choice, 8, stdin);
    return atoi(choice);
}

void timeout(){
    printf("Duh... Your time is up. Come again next time\n");
    exit(1);
}

int main(){
    setup();
    banner();
    srand(time(NULL));
    char* special_request = "i_had_enough_gimme_the_flaaaaag";
    bool deduct_processing = true;
    while(1){
        int decision = decide();
        switch(decision){
            case 1:
                wait();
                break;
            case 2:
                deduct_processing = call();
                break;
            case 3:
                hesitate();
                break;
            case 4:
                leave();
            default:
                invalid_decision();
                break;
        }
        check_credit();
        deduct_processing_fee(deduct_processing);
        
        if (!strcmp(hidden_access_input, special_request)){
            give_extra_feature();
        }
    }
    return 0;
}