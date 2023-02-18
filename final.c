#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 100

// Struct to represent an Automaton
struct Automaton {
    int nb_states;
    int initial_states[MAX_STATES]; // The initial state can be more than one, so we need to store them in an array
    int nb_initial_states;
    int final_states[MAX_STATES];
    int nb_final_states;
    int from[MAX_STATES];
    int to[MAX_STATES];
    char symbol[MAX_SYMBOLS];
    int ligne_nmbr;
    int nb_transitions;
    int final_states2[MAX_STATES];
    int nb_final_states2;
};
void read_automaton_from_file(char *filename, struct Automaton *automaton) {
    // Open the file for reading
    FILE *file = fopen(filename, "r");
    // Check if the file was opened successfully
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    //count the number of lines in the file
    automaton->ligne_nmbr = 0;
    char c;
    while ((c = fgetc(file)) != EOF){
        if (c == '\n'){
            automaton->ligne_nmbr++;
        }
    }
    automaton->ligne_nmbr=automaton->ligne_nmbr +1 ;
    printf("The number of lines in the file is %d\n", automaton->ligne_nmbr);
    //copy every line in the file to the struct
    rewind(file);
    int Max_trasitions = automaton->ligne_nmbr -2;
    for (int i = 0; i <= Max_trasitions -1;i++) {
        fscanf(file, "%d %d %c", &automaton->from[i], &automaton->to[i], &automaton->symbol[i]) ;
        automaton->nb_transitions++;
    }
    
    //print the transitions
    for (int i = 0; i <= Max_trasitions -1 ; i++){
        printf("%d %d %c \n", automaton->from[i], automaton->to[i], automaton->symbol[i]);
    }
    automaton->nb_transitions=Max_trasitions;
    // Read the file and store initial and final states as a string
    char initial_states_str[50], initial_states_str2[50] ,final_states_str[50],final_states_str2[50];
    fgets(initial_states_str, 50, file);
    fgets(final_states_str, 50, file);
    

    // Convert the states to arrays
    int i = 0, j = 0, n;
    char *token;
    token = strtok(initial_states_str, ",");
    while (token != NULL) {
        automaton->initial_states[i] = atoi(token);
        i++;
        token = strtok(NULL, ",");
    }
    automaton->nb_initial_states = i;

    token = strtok(final_states_str, ",");
    while (token != NULL) {
        automaton->final_states[j] = atoi(token);
        j++;
        token = strtok(NULL, ",");
    }
    automaton->nb_final_states = j -1 ;
    // Reset the file pointer to the beginning of the file
    rewind(file);
    char u[100];
    // Read and discard the first n-1 lines
    for (i = 0; i < automaton->ligne_nmbr-1; i++) {
        fgets(u, 100, file);
    }

    // Read the last line of the file and store it in 'u'
    fgets(final_states_str2, 50, file);

    //converte the last line to array
    int l = 0;
    char *token2;
    token2 = strtok(final_states_str2, ",");
    while (token2 != NULL) {
        automaton->final_states2[l] = atoi(token2);
        l++;
        token2 = strtok(NULL, ",");
    }
    automaton->nb_final_states2 = l ;
    // Print the initial states
    printf("initial states: ");
    int k ;
    for ( k = 0; k < automaton->nb_final_states; k++) {
        printf("%d ", automaton->final_states[k]);
    }
    automaton->nb_final_states=k;
    printf("\n");
    // Print the final states
    printf("final states: ");
    int v ; 
    for ( v = 0; v < automaton->nb_final_states2; v++) {
        printf("%d ", automaton->final_states2[v]);
    }
    automaton->nb_final_states2=v ;


    // Close the file
    fclose(file);
}

 void create_dot_file(char *filename, struct Automaton *automaton) {
  FILE *file = fopen(filename, "w");
  // Check if the file was successfully opened
  if (file == NULL) {
    // If not, print an error message and exit the program
    printf("Error opening file!\n");
    exit(1);
  }

  // Write the header of the dot file
  // The header of the dot file contains the following information:
  // The digraph keyword indicates that the file is a directed graph.
  // The rankdir=LR keyword indicates that the graph should be drawn from left to right.
  // The node [shape=circle] keyword indicates that all nodes should be drawn as circles.
  // The initial [style=invis] keyword indicates that the initial state should be drawn as an invisible node.

  fprintf(file, "digraph {\n");
  fprintf(file, "  rankdir=LR;\n");
  fprintf(file, "  node [shape=circle];\n");
  fprintf(file, "  initial [style=invis];\n");
  for (int i = 0; i < automaton->nb_initial_states; i++) {
    fprintf(file, "  initial -> q%d;\n", automaton->final_states[i]);
  }
//print the transition 
for(int i=0;i<automaton->nb_transitions;i++){
    fprintf(file,"q%d -> q%d [label=\"%c\"];\n",automaton->from[i],automaton->to[i],automaton->symbol[i]);
}
//print the final states
for(int i=0;i<automaton->nb_final_states2;i++){
    fprintf(file,"q%d [shape=doublecircle];\n",automaton->final_states2[i]);
}
    // Write the footer of the dot file
    fprintf(file, "}");
    
    // Close the file
    fclose(file);
  
  






}
int main(){
    struct Automaton automaton;
    read_automaton_from_file("Fichier1.txt",&automaton);
    create_dot_file("automaton.dot",&automaton);
    return 0 ;
}
