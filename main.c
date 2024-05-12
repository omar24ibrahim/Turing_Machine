#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Some variables
const char actions[4] = {'L', 'R', 'Y', 'N'};
int n;              // Number of States
char buf[1000];     // Buffer
int initial;        // Initial State
int head;           // Head Position
char empty[1];      // Empty Symbol
char tape[1000];    // Input Tape
char g[1000];       // Gamma
char alpha[1000];    // Alphabet
int h;              // Size of Gamma
int l_alpha;        // Size of Alphabet

// Actions
enum Action {
    L = 1,
    R = 2,
    Y = 3,
    N = 4
}Action;

// Transition Structure
struct Transition{
    int current_state, next_state;
    char input_symbol, new_symbol;
    enum Action action;
} Transition;

// Initializing Turing Machine variables
void init_TM()
{
    printf("Enter number of states: ");
    scanf("%d", &n);
    if(n <= 0)
    {
        printf("Invalid number of states.\n");
        exit(-1);
    }
    printf("Enter the alphabet (comma separated): ");
    scanf("%s", buf);
    l_alpha = strlen(buf)/2+1;
    for(int i = 0; i < l_alpha; i++)
    {
        if((i < (l_alpha-1)) && (buf[2*i+1] != ','))
        {
            printf("Invalid alphabet symbols.\n");
            exit(-1);
        }
        alpha[i] = buf[2*i];
    }
    printf("Enter the gamma (comma separated and last element is corresponding to the empty symbol)\n");
    printf("[If your transition function has the transitions according to (<), please enter it in the beginning of your gamma.]: ");
    scanf("%s", buf);
    h = strlen(buf)/2+1;
    for(int i = 0; i < h; i++)
    {
        if(((i < (l_alpha-1)) && (buf[2*i+1] != ',')) || ((buf[2*i] == '<') && (i != 0)))
        {
            printf("Invalid gamma symbols.\n");
            exit(-1);
        }
        g[i] = buf[2*i];
    }
    if(!((strlen(alpha) + 1) <= strlen(g)))
    {
        printf("Invalid alphabet and gamma combination\n");
        exit(-1);
    }
    for(int i = 0; i < strlen(alpha); i++)
    {
        char *c = strchr(g, alpha[i]);
        if(c == NULL)
        {
            printf("Invalid alphabet and gamma combination\n");
            exit(-1);
        }
    }
    empty[0] = g[h-1];
    printf("Enter initial state (first state is 0): ");
    scanf("%d", &initial);
    if(initial < 0 || initial >= n)
    {
        printf("Invalid initial state.\n");
        exit(-1);
    }
}

// Adding Transition Function specifications
void input_Transitions(struct Transition *t)
{
    printf("Enter transition function:\n");
    printf("In the form of: 'number of next state','next symbol','action {L,R,N,Y}'\n");
    for(int i = 0; i < n*h; i++)
    {
        t[i].current_state = i/h;
        t[i].input_symbol = g[i%h];
        printf("(q%d,%c) --> ", t[i].current_state, t[i].input_symbol);
        scanf("%s", buf);
        char *c;
        c = strchr(buf, ',');
        int index;
        if(c != NULL)
        {
            index = (int)(c-buf);
        }
        else
        {
            printf("Invalid transition.\n");
            exit(-1);
        }
        char num[index];
        for(int j = 0; j < index; j++)
        {
            if((buf[j] < '0') || (buf[j] > '9'))
            {
                printf("Invalid next state entered.\n");
                exit(-1);
            }
            num[j] = buf[j];
        }
        if(atoi(num) < 0 || atoi(num) >= n)
        {
            printf("Invalid next state entered.\n");
            exit(-1);
        }
        t[i].next_state = atoi(num);
        c = strchr(g, buf[index+1]);
        if(c == NULL)
        {
            printf("Invalid symbol entered.\n");
            exit(-1);
        }
        t[i].new_symbol = buf[index+1];
        switch(buf[index+3])
        {
            case 'L':
            t[i].action = L;
            break;
            case 'R':
            t[i].action = R;
            break;
            case 'Y':
            t[i].action = Y;
            break;
            case 'N':
            t[i].action = N;
            break;
            default:
            printf("Invalid action entered.\n");
            exit(-1);
            break;
        }
    }
}

// Transition representation
void print_Transition(struct Transition t)
{
    printf("(q%d, %c) ---> (q%d, %c, %c)", t.current_state, t.input_symbol, t.next_state, t.new_symbol, actions[t.action-1]);
}

// Tape representation
void print_Tape(int head_pos)
{
    for(int i = 0; i <= strlen(tape); i++)
    {
        if(i == head_pos)
        {
            printf("(%c)", tape[i]);
        }
        else
        {
            printf("%c", tape[i]);
        }
    }
}

// Computation representation
void print_Transition_part(struct Transition t, int head_pos)
{
    printf("(q%d, ", t.current_state);
    print_Tape(head_pos);
    printf(") ---> (q%d, %c, %c)\n", t.next_state, t.new_symbol, actions[t.action-1]);
}

// Running Turing Machine
void run(int i, struct Transition *t)
{
    while(1)
    {
        if(i < 0)
        {
            printf("Head reached unavailable position, check your transition function.\n");
            exit(-1);
        }
        if(i >= strlen(tape))
        {
            int j = i;
            while(j >= strlen(tape))
            {
                strcat(tape,empty);
            }
        }
        char *c;
        c = strchr(g, tape[i]);
        if(c != NULL)
        {
            int ind = (h*initial) + (int)(c-g);
            print_Transition_part(t[ind],i);
            tape[i] = t[ind].new_symbol;
            initial = t[ind].next_state;
            switch(t[ind].action)
            {
            case 1:
                i--;
                break;
            case 2:
                i++;
                break;
            case 3:
                printf("Accepted\n");
                exit(0);
                break;
            case 4:
                printf("Rejected / Error\n");
                exit(0);
                break;
            }
        }
        else
        {
            printf("Invalid tape content.\n");
            exit(-1);
        }
    }
}

// Adding Tape and Head Position to Turing Machine
void input_Tape_Head()
{
    printf("\nEnter the input tape: ");
    scanf("%s", buf);
    for(int i = 0; i < strlen(buf); i++)
    {
        if(buf[i] == '#')
        {
            continue;
        }
        char *c;
        c = strchr(alpha, buf[i]);
        if(c == NULL)
        {
            printf("Invalid input string.\n");
            exit(-1);
        }
    }
    printf("Enter head position (first character you entered is considered 1 and left-end mark is considered 0 and is automatically entered): ");
    scanf("%d", &head);
    printf("\n");
    if(head < 0)
    {
        printf("Invalid head position.\n");
        exit(-1);
    }
    tape[0] = '<';
    strcat(tape, buf);
    int i = head;
    if(i >= strlen(tape))
    {
        int j = i;
        while(j >= strlen(tape))
        {
            strcat(tape,empty);
        }
    }
}

// Turing Machine representation
void print_TM_info(struct Transition *t)
{
    printf("\nTuring Machine Info. <K, %c, %c, s, %c>:\n", 228, 226, 235);
    printf("_________________________________________\n\n");
    printf("K = {");
    for(int i = 0; i < n-1; i++)
    {
        printf("q%d, ", i);
    }
    printf("q%d}\n", n-1);
    printf("%c = {", 228);
    for(int i = 0; i < strlen(alpha)-1; i++)
    {
        printf("%c, ", alpha[i]);
    }
    printf("%c}\n", alpha[strlen(alpha)-1]);
    printf("%c = {", 226);
    for(int i = 0; i < strlen(g)-1; i++)
    {
        printf("%c, ", g[i]);
    }
    printf("%c}\n", g[strlen(g)-1]);
    printf("s = q%d\n", initial);
    printf("%c = {\n", 235);
    for(int i = 0; i < (n*h)-1; i++)
    {
        print_Transition(t[i]);
        printf(" ,\n");
    }
    print_Transition(t[(n*h)-1]);
    printf("\n}\n");
}

// Turing Machine Transition Function represented on tape
void print_TM_01s(struct Transition *t)
{
    printf("Universal Turing Machine input:\n");
    printf("_______________________________\n\n");
    for(int i = 0; i < n*h; i++)
    {
        for(int j = 0; j <= t[i].current_state; j++)
            printf("1");
        printf("0");
        char *c;
        c = strchr(g, t[i].input_symbol);
        for(int j = 0; j <= (int)(c-g); j++)
            printf("1");
        printf("0");
        for(int j = 0; j < t[i].next_state; j++)
            printf("1");
        printf("0");
        c = strchr(g, t[i].new_symbol);
        for(int j = 0; j <= (int)(c-g); j++)
            printf("1");
        printf("0");
        for(int j = 0; j < t[i].action; j++)
            printf("1");
        printf("00");
    }
    printf("\n");
}

int main()
{
    init_TM();
    struct Transition t[n*h];
    input_Transitions(t);
    printf("\n");
    print_TM_info(t);
    input_Tape_Head();
    int i = head;
    printf("\n");
    print_TM_01s(t);
    printf("\nInput Tape: ");
    printf("%s\n\n", tape);
    printf("\n");
    run(i, t);
    return 0;
}
