#include <stdio.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 100

// Struct to represent a Transition
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

int match_input(struct Automate *automate, char *input) {
    int current_state = automate->initial_state;
    int symbol_index = 0;
    int input_length = strlen(input);
    while (symbol_index < input_length) {
        int symbol = input[symbol_index];
        if (automate->transition_table[current_state][symbol] != -1) {
            current_state = automate->transition_table[current_state][symbol];
            symbol_index++;
        } else {
            return 0;
        }
    }
    for (int i = 0; i < automate->nb_final_states; i++) {
        if (current_state == automate->final_states[i]) {
            return 1;
        }
    }
    return 0;
}

int main() {
    // Create the A1 automaton
    struct Automate A1;
    A1.nb_states = 3;
    A1.initial_state = 0;
    A1.nb_final_states = 1;
    A1.final_states[0] = 2;

    // Initialize the transition table to -1
    for (int i = 0; i < MAX_STATES; i++) {
        for (int j = 0; j < MAX_SYMBOLS; j++) {
            A1.transition_table[i][j] = -1;
        }
    }

    // Define the transitions of the A1 automaton
    struct Transition transitions[] = {
        {0, 1, "a"},
        {1, 2, "b"},
        {2, 2, "a"},
        {2, 2, "b"}
    };
    int nb_transitions = sizeof(transitions) / sizeof(transitions[0]);

    // Populate the transition table of the A1 automaton
    for (int i = 0; i < nb_transitions; i++) {
        int from = transitions[i].from;
        int to = transitions[i].to;
        int symbol = transitions[i].symbol[0];
        A1.transition_table[from][symbol] = to;
    }

    // Test the A1 automaton
    char input1[] = "ab";
    char input2[] = "aba";
    char input3[] = "abab";
    if (match_input(&A1, input1)) {
        printf("%s is accepted\n", input1);
    } else {
        printf("%s is rejected\n", input1);
    }
    if (match_input(&A1, input2)) {
        printf("%s is accepted\n", input2);
    } else {
        printf("%s is rejected\n", input2);
    }
    if (match_input(&A1, input3)) {
        printf("%s is accepted\n", input3);
    } else {
        printf("%s is rejected\n", input3);
    }
    write_automate_to_file("A1.txt", A1);
    create_dot_file("A1.dot", A1);
    return 0;
}
