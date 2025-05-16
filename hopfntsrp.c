
#include "hopfntsrp.h"

#define RECALL_ITER   3 // Number of iterations for recall
#define SPACE_CHAR   32 // Character representing the neuron state (off)  
#define SOLID_BLOCK 254 // Character representing the neuron state (on)

float weights[NUM_NEURONS][NUM_NEURONS];


int reference_pattern_matrix[] = {
                                0, 1, 1, 1, 1, 1, 0,
                                1, 0, 0, 0, 0, 0, 1,
                                1, 0, 0, 0, 0, 0, 1,
                                1, 0, 0, 0, 0, 0, 1,
                                1, 0, 0, 0, 0, 0, 1,
                                0, 1, 1, 1, 1, 1, 0,
                                0, 0, 0, 0, 0, 0, 1,
                                0, 0, 0, 0, 0, 0, 1,
                                0, 0, 0, 0, 0, 0, 1,
                                0, 0, 0, 0, 0, 0, 1,
                                0, 1, 1, 1, 1, 1, 0 };
int distorted_pattern_matrix[] = {
                                 0, 0, 1, 0, 1, 1, 0,
                                 0, 0, 1, 0, 0, 0, 1,
                                 0, 1, 0, 1, 0, 0, 0,
                                 0, 1, 0, 1, 1, 0, 0,
                                 1, 0, 0, 0, 0, 0, 1,
                                 0, 0, 0, 1, 0, 1, 0,
                                 1, 1, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 1, 0, 1,
                                 0, 1, 0, 1, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 1,
                                 0, 1, 0, 1, 0, 0, 0 };


void
init_hopfield_weights(float weights[][NUM_NEURONS]) 
{
  for (int i = 0; i < NUM_NEURONS; i++) {
    for (int j = 0; j < NUM_NEURONS; j++)
      weights[i][j] = 0.0;
  }
}


void
hebbian_training(float weights[][NUM_NEURONS], int pattern[NUM_NEURONS]) 
{
  for (int i = 0; i < NUM_NEURONS; i++) {
    for (int j = 0; j < NUM_NEURONS; j++) {
      if (i != j) {
         // Update weights using Hebbian learning rule
         weights[i][j] += (2 * pattern[i] - 1) * (2 * pattern[j] - 1);
      }
    }
  }
}


void
synchronous_update(float weights[][NUM_NEURONS], int neurons[NUM_NEURONS]) 
{
   // Create a temporary array to store the new state of neurons
   int new_neurons[NUM_NEURONS] = { 0 };

   for (int i = 0; i < NUM_NEURONS; i++) {
      float sum = 0.0;
      for (int j = 0; j < NUM_NEURONS; j++) {
         // Convert current state of neurons j (0 or 1)
         // to bipolar (-1 or +1)
         float bipolar_j_state = (neurons[j] == 1) ? 1.0f : -1.0f;
         sum += weights[i][j] * bipolar_j_state;
      }
      // Determine next state (0 or 1 based on threshold)
      new_neurons[i] = (sum >= 0) ? 1 : 0;
   }
   // Update all neurons simultaneously
   for (int i = 0; i < NUM_NEURONS; i++) {
      neurons[i] = new_neurons[i];
   }
}


void
render_pattern(int pattern[NUM_NEURONS]) 
{
  for (int i = 0; i < NUM_NEURONS; i++) {
    printf("%c ", pattern[i] ? SOLID_BLOCK : SPACE_CHAR);
    if ((i + 1) % 7 == 0) {
      printf("\n");
    }
  }
  printf("\n");
}

int main() 
{

  // Initialize weights
  init_hopfield_weights(weights);

  // Train network
  hebbian_training(weights, reference_pattern_matrix);

  // Recall process
  printf("\nRecall process for the distorted pattern '9'\n");
  render_pattern(distorted_pattern_matrix);

  for (int itr = 0; itr < RECALL_ITER; itr++) {
    synchronous_update(weights, distorted_pattern_matrix);
    printf("Iteration %d:\n", itr + 1);
    render_pattern(distorted_pattern_matrix);
  }

  return 0;
}

