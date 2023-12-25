#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

//ini untuk define max entries dan max panjang username
#define MAX_USERNAME_LENGTH 20
#define MAX_ENTRIES 100

//ini untuk enter ke menu lain
void pressEnter() {
	char key;
	printf("Press enter to continue ...");
	do {
  		key = getch();
 	} while (key != '\r');
}
//ini untuk generate random number ama random operator
void generate_question(int *num1, int *num2, char *operator) {
    *num1 = rand() % 100 + 1;
    *num2 = rand() % 100 + 1;
    *operator = rand() % 2 == 0 ? '+' : '-';
}

//ini untuk display soalnya
int ask_question(int num1, int num2, char operator) {
    int answer;
    printf("%d %c %d = ", num1, operator, num2);
    scanf("%d", &answer);
    return answer;
}

//ini untuk cek jwabannyannya bener ato salah
int check_answer(int answer, int num1, int num2, char operator) {
    switch (operator) {
        case '+':
            return answer == num1 + num2;
        case '-':
            return answer == num1 - num2;
        default:
            return 0;
    }
}

// ini untuk display menu
void display_menu() {
	printf(" ______               _   _                          _   _       _____ \n");
    printf("|  ____|             | | | |                        | | (_)     / ____|\n");
    printf("| |__ _ __ ___   __ _| |_| |__   ___ _ __ ___   __ _| |_ _  ___| (___  \n");
    printf("|  __| '_ ` _ \\ / _` | __| '_ \\ / _ \\ '_ ` _ \\ / _` | __| |/ __|\\___ \\ \n");
    printf("| |  | | | | | | (_| | |_| | | |  __/ | | | | | (_| | |_| | (__ ____) |\n");
    printf("|_|  |_| |_| |_|\\__,_|\\__|_| |_|\\___|_| |_| |_|\\__,_|\\__|_|\\___|_____/ \n");

	printf("\nWelcome To FmathematicS!\n");
    printf("1. Play\n");
    printf("2. Highscores\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

//ini untuk nyimpen highscore di file
void save_highscore(char *username, int score) {
    FILE *fptr = fopen("highscores.txt", "a");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fptr, "%s#%d\n", username, score);
    fclose(fptr);
}

//ini untuk munculin highscore
void display_highscores() {
    FILE *fptr = fopen("highscores.txt", "r");
    if (fptr == NULL) {
        printf("No highscores found!\n");
        return;
    }
    
	//ini untuk ngeread entries ke temp array
    int num_entries = 0;
    char usernames[MAX_ENTRIES][MAX_USERNAME_LENGTH];
    int scores[MAX_ENTRIES];
	
	//ini untuk baca di file
    while (num_entries < MAX_ENTRIES) {
    	fscanf(fptr, "%[^#]#%d\n", usernames[num_entries], &scores[num_entries]);
    	
    //ini untuk ngeoverwrite data dengan highscore yang lebih besar
  	for (int i=0;i<num_entries;i++) {
   		if (strcmp(usernames[i], usernames[num_entries]) == 0) {
    		if (scores[i] < scores[num_entries]) {
     			scores[i] = scores[num_entries];
     			num_entries--;
    			break;
    		}
    		else {
     			num_entries--;
    		}
   		}
  	}
    num_entries++;
        if (feof(fptr)) {
      	break;
  		}
    }
    fclose(fptr);

	//ini untuk sort dari paling tinggi ke paling rendah (pakai bubblesort)
    for (int i = 0; i < num_entries - 1; i++) {
        for (int j = 0; j < num_entries - i - 1; j++) {
            if (scores[j] < scores[j + 1]) {
                int temp_score = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp_score;
				
				//swap variabel
                char temp_username[MAX_USERNAME_LENGTH];
                strcpy(temp_username, usernames[j]);
                strcpy(usernames[j], usernames[j + 1]);
                strcpy(usernames[j + 1], temp_username);
            }
        }
    }
	//ini untuk display highscore yg udh disort
    printf("Highscores :\n");
    for (int i = 0; i < num_entries; i++) {
    	printf("%d. %s: %d\n", i+1, usernames[i], scores[i]);
    }
    
    puts("");
    pressEnter();
    system("cls");
}

//ini biar function prototype aj :)
void exit_menu();

//ini untuk menu
int main() {		
    srand(time(NULL));
    int choice, score = 0;
    char username[MAX_USERNAME_LENGTH];

    do {
        display_menu();
        scanf("%d", &choice); getchar();
        system("cls");

        switch (choice) {
            case 1:
                printf("Enter your username: ");
                scanf("%s", username);
                score = 0;

                while (1) {
                    int num1, num2;
                    char operator;
                    generate_question(&num1, &num2, &operator);
                    int answer = ask_question(num1, num2, operator);
                    if (check_answer(answer, num1, num2, operator)) {
                        printf("Correct!\n");
                        score++;
                    } else {
                        printf("Wrong!\n");
                        printf("Your final score is: %d\n\n\n", score);
                        save_highscore(username, score);
    
                        pressEnter();
                        system("cls");
                        break; 
                    }
                }
                break;
            case 2:
                display_highscores();
                break;
            case 3:
                exit_menu();
                exit(0);
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);

    return 0;
}

//ini special
void exit_menu(){
	printf("                            .:^:.. ..^^:..\n");
    Sleep(1);
    printf("                          ...   ...:.     .......    .\n");
    Sleep(1);
    printf("                            .   . ^.   :..:~~77~~~::..::.. ..\n");
    Sleep(1);
    printf("                          ::::..~..:..:~7~.: :^ ~^:~..:....:^~^:^~^\n");
    Sleep(1);
    printf("                        ..      .. .^!777^~~!?~^~7:^::.  .5BGB##&#7.\n");
    Sleep(1);
    printf("                             .:~!!. .:~^.77?P57P7!^::~::?5B&&#GGG5.\n");
    Sleep(1);
    printf("                          .:^~~^^: YJJGBGP5YY7J7!^^^?7YG##P7^7#&B~:\n");
    Sleep(1);
    printf("                        .^~~:  ~J55PJ~:.       ..~JPBBBY^. .:.JG!:!!^..\n");
    Sleep(1);
    printf("                     ..^7~  .::???.         .~!JG&&#J:       .7!:.^77?!^..\n");
    Sleep(1);
    printf("                   .:~7!:. ^Y^.  ..      .!JPB&&#Y:          .  :7!: ~G5?!:.\n");
    Sleep(1);
    printf("                 .:~7?7..~!!       .:..^?YP&&&G7         .        ~J: .BP7J!:.\n");
    Sleep(1);
    printf("               .:^777~^::7^          :JB&&#BG^ .                   .J! !YYYJ?^.\n");
    Sleep(1);
    printf("              .:!JJJJ: :7G.         ?#&&&&B~                         ?5..^!~~!!:.\n");
    Sleep(1);
    printf("             .:!YYY5~ .J&Y      . .5BBBBBG^                           YP  :?J!~!^.\n");
    Sleep(1);
    printf("             .:!J?YJ^..P&!        P&&&&&#!             ..              #7 .^55?^~:\n");
    Sleep(1);
    printf("              .^7!??^..P#? .  .   ~#&&&&&J:..   ...  .   ..  ...     . 5#..:J57~!:.\n");
    Sleep(1);
    printf("              .:!J~~^.?G#5      .:.^JGBBBP5Y!^75GBGP5PJYPGPP5YYJ?!^    !&:.:??~?~:.\n");
    Sleep(1);
    printf("               .^?5^:.JPBP!       .:::.. .!YYY&&&###&&&&YG##&&&&#B5:   !&:.^~!5J~.\n");
    Sleep(1);
    printf("                .^??:.^^?77..                 ^:.  ..P&G:^&&&&&&&&7    PG ~7:JP7:.\n");
    Sleep(1);
    printf("                .:^7? .~~J?7!                 .      7#^ P&&&&&&G^    :&^ 7?5?!:.\n");
    Sleep(1);
    printf("                  .^J5.:!JPBBY            .:.       ^5^ 7###&#P^      G7..7G5!:.\n");
    Sleep(1);
    printf("                   .^?5~^~:~PBP~.?!~: ^^7~^!^     .7: ~#&&#5~        ~~:.:PY~:.\n");
    Sleep(1);
    printf("                    .^!5J7..~!B&PJY?J^J?YGY?7!:..^^:?#@&G7.        .~.::^Y!^.\n");
    Sleep(1);
    printf("                     .:^??J!77JY57 .: :?#BYGG!7~:7G&#5~.           .~^!J5!:.\n");
    Sleep(1);
    printf("                       .:~?JY~..... :.^!J^^!7~7PGPJ~.          ... ^?Y57:.\n");
    Sleep(1);
    printf("                          :~75P~:.  ^^!!^~!JYJ57:..^^....:^!:  ...5GP7^.\n");
    Sleep(1);
    printf("                          ::.:~^7.JY^?77Y5Y7^..::~??5J???5J: :?Y!J5!:.\n");
    Sleep(1);
    printf("                           .  .^.7G&###B5!^:.:.::......~?J?YB#BY7^:.\n");
    Sleep(1);
    printf("                              .^^YJ5###BG5J7!7JYPPGYJ??YPPPY?7~:.\n");
    Sleep(1);
    printf("                              ..:^~^^........^~!~!!!!~^^::...\n");
    Sleep(1);
    printf("\n");
    Sleep(1);
    printf("                        o---------------------------------------------o\n");
    Sleep(1);
    printf("                        |      Breaking and Overcoming Challenges     |\n");
    Sleep(1);
    printf("                        |    Through Courage Hardwork and Persistence |\n");
    Sleep(1);
    printf("                        o---------------------------------------------o\n");
}
