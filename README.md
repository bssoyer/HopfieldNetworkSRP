# Hopfield Network for Pattern Recall in C

## Introduction

This project implements a Hopfield network using the C programming language. It demonstrates the network's ability to function as an associative (content-addressable) memory, capable of recalling a stored pattern when presented with a noisy or incomplete version. This example focuses on storing and recalling simple patterns like digital digits on a grid.
The specific reference pattern for the Hopfield network is the `9` digit encoded on a 7x11 matrix. The corresponding distorted pattern is stored again in a 7x11 matrix. 

### Hopfield Networks
A Hopfield network is a recurrent artificial neural network popularized by John Hopfield. Key characteristics include:
* **Recurrent Connections:** Neurons are typically fully connected (often excluding self-connections), and information flows cyclically through the network.
* **Associative Memory:** They can store patterns as stable states (attractors) in the network's dynamics.
* **Pattern Completion/Correction:** When initialized with a partial or corrupted pattern, the network state evolves iteratively until it converges (hopefully) to the closest stored pattern. This is achieved by minimizing an associated "energy" function.

### Hebbian Learning
The network in this project is trained using a principle derived from **Hebbian learning**. This biologically inspired concept is often summarized as "neurons that fire together, wire together." In practice for this Hopfield network:

* The connection strengths (weights) between neurons are calculated based on the correlation between neuron states in the pattern(s) to be stored.
* If two neurons are typically in the same state (+1/+1 or -1/-1) across the stored patterns, their connection weight is strengthened (positive).
* If they are typically in opposite states (+1/-1), the connection weight becomes inhibitory (negative).
* This process shapes the network's energy landscape, creating stable minima corresponding to the stored reference pattern(s).

This implementation allows exploration of fundamental Hopfield network dynamics and the application of Hebbian learning for a single pattern storage and recall.

### The Role of the Energy Function
The energy function provides a theoretical understanding of why the network settles into stable states (attractors). Each update that changes a neuron's state decreases (or does not change) this energy, ensuring the network doesn't oscillate indefinitely and eventually finds a minimum. The stored patterns ideally correspond to these energy minima.
Why have we not applied the energy function? Because it is not strictly necessary for the network to operate. Our network stores patterns by modifying weights (Hebbian learning) and recalls patterns by iteratively updating neuron states based on the weighted sum of inputs. This update process implicitly follows the gradient of the energy landscape without your code needing to calculate the value of `E` at each step. The network "finds its way" to a minimum based on local rules.
If our network successfully stores and recalls patterns, the absence of an explicit energy calculation function doesn't mean the core associative memory demonstration is flawed. The primary goal is often to show this recall behaviour. For the demonstration projects, HopfieldNetworkSRP/LCP  using the energy function is not a significant drawback for demonstrating the fundamental recall capabilities of our Hopfield network.
However, calculating the energy of different states (initial distorted patterns, intermediate states, final converged patterns, stored reference patterns) can provide valuable insights since
+ We can numerically verify that stored patterns are indeed low-energy states.
+ We can see if the energy decreases during the recall process.
+ It helps understand the "depth" of attractors or diagnose issues if the network gets stuck in unexpected states.

These would be interesting extensions to the Hopfield network projects.

### Setting the Environment
Visual Studio Community 2022 is the preferred platform for running this project, which does not use external libraries or open-source software. However, previous releases of Visual Studio (2019, 2017, 2015, etc.) shall not pose any problems with the source code, because the app is written in plain C language.
 
Visit https://visualstudio.microsoft.com/tr/downloads/?cid=learn-onpage-download-install-visual-studio-page-cta to install the community edition.
After installing Visual Studio Community 2022, click on the solution file `HopfieldNetHebbian.sln` to open the development environment. 
Select `> Build > Build HopfieldNetworkSRP`. After the build you can locate the executable in `C:\...\HopfieldNetworkSRP\x64\Debug` directory.
