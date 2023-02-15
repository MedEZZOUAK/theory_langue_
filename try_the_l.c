#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 100

// Struct to store a transition from a state to another
struct Transition {
  int from;
  int to;
  char symbol[MAX_SYMBOLS];
};


// Struct to represent an Automaton
struct Automate {
  int nb_states;
  int initial_state;
  int final_states[MAX_STATES];
  int nb_final_states;
  int transition_table[MAX_STATES][MAX_SYMBOLS];
};

// Writes an Automaton to a file
void write_automate_to_file(char *filename, struct Automate automate) {
  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }

  // Write the number of states, the initial state and the number of final states
  fprintf(file, "%d\n", automate.nb_states);
  fprintf(file, "%d\n", automate.initial_state);
  fprintf(file, "%d\n", automate.nb_final_states);

  // Write the final states
  for (int i = 0; i < automate.nb_final_states; i++) {
    fprintf(file, "%d ", automate.final_states[i]);
  }
  fprintf(file, "\n");

  // Write the transition table
  for (int i = 0; i < automate.nb_states; i++) {
    for (int j = 0; j < MAX_SYMBOLS; j++) {
      fprintf(file, "%d ", automate.transition_table[i][j]);
    }
    fprintf(file, "\n");
  }

  // Close the file
  fclose(file);
}

// Function to read an Automate structure from a file
void read_automate_from_file(char *filename, struct Automate *automate) {
  // Open the file for reading
  FILE *file = fopen(filename, "r");
  // Check if the file was successfully opened
  if (file == NULL) {
    // If not, print an error message and exit the program
    printf("Error opening file!\n");
    exit(1);
  }

  // Read the number of states from the file
  fscanf(file, "%d", &automate->nb_states);
  // Read the initial state from the file
  fscanf(file, "%d", &automate->initial_state);
  // Read the number of final states from the file
  fscanf(file, "%d", &automate->nb_final_states);
  // Read the final states from the file
  for (int i = 0; i < automate->nb_final_states; i++) {
    fscanf(file, "%d", &automate->final_states[i]);
  }
  // Read the transition table from the file
  for (int i = 0; i < automate->nb_states; i++) {
    for (int j = 0; j < MAX_SYMBOLS; j++) {
      fscanf(file, "%d", &automate->transition_table[i][j]);
    }
  }
  // Close the file
  fclose(file);

}
// Function to create a dot file from an Automaton
void create_dot_file(char *filename, struct Automate automate) {
  // Open the file for writing
  FILE *file = fopen(filename, "w");
  // Check if the file was opened successfully
  if (file == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }

  // Write the header of the dot file
  fprintf(file, "digraph {\n");
  fprintf(file, "  rankdir=LR;\n");
  fprintf(file, "  node [shape=circle];\n");
  fprintf(file, "  initial [style=invis];\n");

  // Write the initial state of the automaton
  fprintf(file, "  initial -> q%d;\n", automate.initial_state);

  // Write the transitions of the automaton
  for (int i = 0; i < automate.nb_states; i++) {
    for (int j = 0; j < MAX_SYMBOLS; j++) {
      int next_state = automate.transition_table[i][j];
      if (next_state != -1) {
        fprintf(file, "  q%d -> q%d [label=%d];\n", i, next_state, j);
      }
    }
  }

  // Write the final states of the automaton
  for (int i = 0; i < automate.nb_final_states; i++) {
    fprintf(file, "  q%d [shape=doublecircle];\n", automate.final_states[i]);
  }

  // Close the dot file
  fprintf(file, "}\n");
  fclose(file);
}

// Download and install Graphviz: Go to the Graphviz website (https://www.graphviz.org/), and follow the instructions to download and install the software.

// Open Graphviz: Start Graphviz, and you'll see the "Graphviz DOT Editor" window.

// Load the .dot file: Click on "File" and then "Open". Locate your .dot file and select it. The file will be loaded into the editor.

// Generate the graph: To generate the graph, click on "File" and then "Generate Graph". A window will pop up, asking you to choose the format of the output file. You can choose any format you like, but PNG is a popular choice. After choosing the format, select a location to save the generated graph and click "Save".

// View the generated graph: The generated graph will be saved as an image file. You can open the image file with any image viewer, such as Windows Photo Viewer or Microsoft Paint.

int main(){
  
   struct Automate a1 = {};


  // Declare the automaton
  struct Automate A1 = {
    .nb_states = 3,
    .initial_state = 0,
    .nb_final_states = 1,
    .final_states = {2},
    .transition_table = {
      // a
      {1, 0, 0},
      // b
      {0, 2, 0},
      // c
      {0, 0, 2},
    },
  };

  // Test the automaton with some input strings
  char input1[] = "abcab";
  int current_state = A1.initial_state;

  for (int i = 0; i < strlen(input1); i++) {
    char symbol = input1[i];
    int symbol_index = symbol - 'a'; // Assumes symbols are characters 'a', 'b', 'c', ...

    current_state = A1.transition_table[current_state][symbol_index];
  }

  // Check if the final state is an accepting state
  int is_accepting = 0;
  for (int i = 0; i < A1.nb_final_states; i++) {
    if (current_state == A1.final_states[i]) {
      is_accepting = 1;
      break;
    }
  }

  printf("Input string: %s\n", input1);
  printf("Final state: %d\n", current_state);
  printf("Is accepting: %s\n", is_accepting ? "yes" : "no");

  char input2[] = "aabbc";
  current_state = A1.initial_state;

  for (int i = 0; i < strlen(input2); i++) {
    char symbol = input2[i];
    int symbol_index = symbol - 'a'; // Assumes symbols are characters 'a', 'b', 'c', ...

    current_state = A1.transition_table[current_state][symbol_index];
  }

  // Check if the final state is an accepting state
  is_accepting = 0;
  for (int i = 0; i < A1.nb_final_states; i++) {
    if (current_state == A1.final_states[i]) {
      is_accepting = 1;
      break;
    }
  }
  
  printf("Input string: %s\n", input2);
  printf("Final state: %d\n", current_state);
  printf("Is accepting: %s\n", is_accepting ? "yes" : "no");
    return 0 ;

}