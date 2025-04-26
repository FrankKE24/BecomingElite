#if !defined(records2)
#define records2


struct Student{
    char RegNo[12];
    char student_passwd[11];
    char full_name[30];
    char mean_grade[5];
    char stream[10];
    char DoB[16];
};

struct Lecturer{
    char passkey[12];
    char username[17];
    char name[14];
};

struct Student student;
struct Lecturer lec1;



#endif // records2
