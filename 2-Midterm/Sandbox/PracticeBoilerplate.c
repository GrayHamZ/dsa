#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXHASH 23
#define EMPTY 0
#define DELETED 1
#define OCCUPIED 2

/****************************************
 *   personalInfo (Computer Word Encoding)
 *
 *   //Bit 7 : Status            (1 = Active, 0 = Inactive)
 *   //Bit 6 : Nationality       (0 = Filipino, 1 = Foreigner)
 *   //Bit 5 : Enrollment Status (0 = Regular, 1 = Irregular)
 *   //Bit 4 : Gender            (0 = Male, 1 = Female)
 *   //Bits 3-2 : Year Level     (00=1st, 01=2nd, 10=3rd, 11=4th)
 *   //Bits 1-0 : Program        (00=CS, 01=IT, 10=IS, 11=MATH)
 ****************************************/

typedef unsigned char personalInfo;

typedef struct {
    char fName[32];
    char lName[32];
} studName;

typedef struct {
    char idNum[10];
    studName name;
    personalInfo info;
} student;

typedef struct {
    student stud;
    int flag; // EMPTY, OCCUPIED, DELETED
} hashNode;

typedef hashNode closedHash[MAXHASH];

/****************************************
 *       FUNCTION PROTOTYPES
 ****************************************/

// Computer word extractors
char* getProgram(personalInfo info);
int getYear(personalInfo info);
int getStatus(personalInfo info);

// Hash Table Operations
void initTable(closedHash H);
int hash(char *id);
int insertStudent(closedHash H, student S);
int searchStudent(closedHash H, char *id);
int deleteStudent(closedHash H, char *id);
void displayTable(closedHash H);

// Activity: Remove inactive → store into array set
typedef struct {
    student removed[50];
    int count;
} studSet;

studSet removeInactive(closedHash H);
void displayInactiveSet(studSet S);


/****************************************
 *       FUNCTION DEFINITIONS (EMPTY)
 ****************************************/

char* getProgram(personalInfo info) {
    // TODO: Extract bits 1-0
    char* toReturn = (char *)malloc(sizeof(char) * 5);
    if (toReturn == NULL) return NULL;

    int progHash = (info & 0b00000011);
    //Bits 1-0 : Program        (00=CS, 01=IT, 10=IS, 11=MATH)
    switch (progHash)
    {
    case 0:
        strcpy(toReturn, "CS");
        break;
    case 1:
        strcpy(toReturn, "IT");
        break;
    case 2:
        strcpy(toReturn, "IS");
        break;
    case 3:
        strcpy(toReturn, "MATH");
        break;
    
    default:
        break;
    }

    return toReturn;
}

int getYear(personalInfo info) {
    // TODO: Extract bits 3-2
    //Bits 3-2 : Year Level     (00=1st, 01=2nd, 10=3rd, 11=4th)
    // 00001100
    int yearHash = (info & 0b00001100) >> 2;
    return yearHash + 1;
}

int getStatus(personalInfo info) {
    //Bit 7 : Status            (1 = Active, 0 = Inactive)
    // 10000000
    return (info & 0b10000000) >> 7;
}

void initTable(closedHash H) {
    // TODO: Set flags to EMPTY
    for (int i = 0; i < MAXHASH; i++) {
        H[i].flag = EMPTY;
    }
}

int hash(char *id) {
    // TODO: Compute sum % MAXHASH
    int total = 0;
    for (int i = 0; id[i] != '\0'; i++) {
        total += (int)id[i];
    }
    return total % MAXHASH;
}

int insertStudent(closedHash H, student S) {
    // TODO: Linear probing insertion

    int i;
    int firstDelete = -1;
    int hashId = hash(S.idNum);
    int stop = (hashId + MAXHASH - 1) % MAXHASH;

    for ( i = hashId; i != stop && H[i].flag != EMPTY && strcmp(H[i].stud.idNum, S.idNum) != 0; i = (i + 1) % MAXHASH) {
        if (firstDelete == -1 && H[i].flag == DELETED) {
            firstDelete = i;
        }
    }

    if (H[i].flag == EMPTY || (firstDelete != -1 && strcmp(H[i].stud.idNum, S.idNum) != 0)) {
        if (firstDelete == -1) {
            H[i].flag = OCCUPIED;
            H[i].stud = S;
        } else {
            H[firstDelete].flag = OCCUPIED;
            H[firstDelete].stud = S;            
        }
    }

}

int searchStudent(closedHash H, char *id) {
    // TODO: Linear probing search
    int i;
    int hashId = hash(id);
    int stop = (hashId + MAXHASH - 1) % MAXHASH;

    for ( i = hashId; i != stop && H[i].flag != EMPTY && strcmp(H[i].stud.idNum, id) != 0; i = (i + 1) % MAXHASH) {}
    
    if (strcmp(H[i].stud.idNum, id) == 0) {
        return i;
    }
}

int deleteStudent(closedHash H, char *id) {
    // TODO: Mark entry as DELETED
    int i;
    int hashId = hash(id);
    int stop = (hashId + MAXHASH - 1) % MAXHASH;

    for ( i = hashId; i != stop && H[i].flag != EMPTY && strcmp(H[i].stud.idNum, id) != 0; i = (i + 1) % MAXHASH) {}
    
    if (strcmp(H[i].stud.idNum, id) == 0) {
        H[i]. flag = DELETED;
        return i;
    }
}

void displayTable(closedHash H) {
    // TODO: Print all occupied entries
    printf("Student found at %d\n", searchStudent(H, "2025002"));

    printf("%-10s", "index");
    printf("%-10s", "flag");
    printf("%-10s", "idNum");
    printf("%-10s", "fname");
    printf("%-10s", "lname");
    printf("%-10s", "Program");
    printf("%-10s", "Year");
    printf("%-10s", "Status");

    printf("\n");
    for (int i = 0; i < MAXHASH; i++) {
        if (H[i].flag == OCCUPIED) {
            printf("%-10d",i);
            printf("%-10d", H[i].flag);
            printf("%-10s", H[i].stud.idNum);
            printf("%-10s", H[i].stud.name.fName);
            printf("%-10s", H[i].stud.name.lName);
            printf("%-10s", getProgram(H[i].stud.info));
            printf("%-10d", getYear(H[i].stud.info));
            printf("%-10s", getStatus(H[i].stud.info) == 1 ? "Active": "Inactive");
            printf("\n");
        }
    }
}

studSet removeInactive(closedHash H) {
    // TODO: extract inactive students into S
    studSet toReturn;
    toReturn.count = 0;

    for (int i = 0; i < MAXHASH; i++) {
        if (getStatus(H[i].stud.info) == 0) {
            toReturn.removed[toReturn.count] = H[i].stud;
            toReturn.count++;
            deleteStudent(H, H[i].stud.idNum);
        }
    }

    return toReturn;
}

void displayInactiveSet(studSet S) {
    // TODO: print removed/inactive students

    printf("INACTIVE SET count %d:\n" , S.count);

    printf("%-10s", "index");
    printf("%-10s", "idNum");
    printf("%-10s", "fname");
    printf("%-10s", "lname");
    printf("%-10s", "Program");
    printf("%-10s", "Year");
    printf("%-10s", "Status");

    printf("\n");
    for (int i = 0; i < S.count; i++) {
        printf("%-10d",i);
        printf("%-10s", S.removed[i].idNum);
        printf("%-10s", S.removed[i].name.fName);
        printf("%-10s", S.removed[i].name.lName);
        printf("%-10s", getProgram(S.removed[i].info));
        printf("%-10d", getYear(S.removed[i].info));
        printf("%-10s", getStatus(S.removed[i].info) == 1 ? "Active": "Inactive");
        printf("\n");
    }
}


/****************************************
 *                 MAIN
 ****************************************/

int main() {
    closedHash H;
    initTable(H);

    // --- Example Test Data (20+ students with varied info) ---
    student s1  = {"2025001", {"Alice", "Cruz"},      0b10000000}; // Active, CS, 1st yr, Male, Regular, Filipino
    student s2  = {"2025002", {"Ben", "Reyes"},       0b10000101}; // Active, IT, 2nd yr, Male, Regular, Filipino
    student s3  = {"2025003", {"Clara", "Santos"},    0b10011010}; // Active, IS, 3rd yr, Female, Regular, Filipino
    student s4  = {"2025004", {"David", "Garcia"},    0b10101111}; // Active, MATH, 4th yr, Female, Irregular, Filipino
    student s5  = {"2025005", {"Emma", "Tan"},        0b00000001}; // Inactive, IT, 1st yr, Male, Regular, Filipino
    student s6  = {"2025006", {"Frank", "Wong"},      0b10110100}; // Active, CS, 2nd yr, Male, Irregular, Foreigner
    student s7  = {"2025007", {"Grace", "Lee"},       0b00001000}; // Inactive, CS, 3rd yr, Male, Regular, Filipino
    student s8  = {"2025008", {"Henry", "Nguyen"},    0b10010110}; // Active, IS, 2nd yr, Female, Regular, Foreigner
    student s9  = {"2025009", {"Iris", "Park"},       0b10100011}; // Active, MATH, 1st yr, Female, Irregular, Filipino
    student s10 = {"2025010", {"Jack", "Kim"},        0b00011101}; // Inactive, IT, 4th yr, Female, Regular, Filipino
    student s11 = {"2025011", {"Kate", "Chen"},       0b10001010}; // Active, IS, 3rd yr, Male, Regular, Filipino
    student s12 = {"2025012", {"Leo", "Martinez"},    0b10111000}; // Active, CS, 3rd yr, Male, Irregular, Foreigner
    student s13 = {"2025013", {"Mia", "Lopez"},       0b00000010}; // Inactive, IS, 1st yr, Male, Regular, Filipino
    student s14 = {"2025014", {"Noah", "Perez"},      0b10010001}; // Active, IT, 1st yr, Male, Regular, Foreigner
    student s15 = {"2025015", {"Olivia", "Torres"},   0b10101100}; // Active, CS, 4th yr, Female, Irregular, Filipino
    student s16 = {"2025016", {"Paul", "Gomez"},      0b00001111}; // Inactive, MATH, 4th yr, Female, Regular, Filipino
    student s17 = {"2025017", {"Quinn", "Rivera"},    0b10110110}; // Active, IS, 2nd yr, Female, Irregular, Foreigner
    student s18 = {"2025018", {"Rachel", "Flores"},   0b10000111}; // Active, MATH, 2nd yr, Male, Regular, Filipino
    student s19 = {"2025019", {"Sam", "Diaz"},        0b00011001}; // Inactive, IT, 3rd yr, Female, Regular, Filipino
    student s20 = {"2025020", {"Tina", "Morales"},    0b10101010}; // Active, IS, 3rd yr, Female, Irregular, Filipino
    student s21 = {"2025021", {"Uma", "Castillo"},    0b10010100}; // Active, CS, 2nd yr, Male, Regular, Foreigner
    student s22 = {"2025022", {"Victor", "Ramos"},    0b00000011}; // Inactive, MATH, 1st yr, Male, Regular, Filipino

    insertStudent(H, s1);
    insertStudent(H, s2);
    insertStudent(H, s3);
    insertStudent(H, s4);
    insertStudent(H, s5);
    insertStudent(H, s6);
    insertStudent(H, s7);
    insertStudent(H, s8);
    insertStudent(H, s9);
    insertStudent(H, s10);
    insertStudent(H, s11);
    insertStudent(H, s12);
    insertStudent(H, s13);
    insertStudent(H, s14);
    insertStudent(H, s15);
    insertStudent(H, s16);
    insertStudent(H, s17);
    insertStudent(H, s18);
    insertStudent(H, s19);
    insertStudent(H, s20);
    insertStudent(H, s21);
    insertStudent(H, s22);

    printf("\n--- Hash Table Contents ---\n");
    displayTable(H);

    printf("\n--- Removing Inactive Students ---\n");
    studSet inactive = removeInactive(H);
    displayInactiveSet(inactive);

    printf("\n--- Hash Table After Removal ---\n");
    displayTable(H);

    return 0;
}