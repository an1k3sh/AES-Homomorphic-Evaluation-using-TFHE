# Implementation of the paper "A Homomorphic AES Evaluation in Less than 30 Seconds by Means of TFHE"

## Install TFHElib

To run the code, you first have to install the TFHElibrary (you can find it [here](https://tfhe.github.io/tfhe/)) and apply the patch provided in the file `patch_fft.patch`. The `git clone` command should automatically install version 1.1 of TFHElib, wich we used to implement our work.

```bash
git clone https://github.com/tfhe/tfhe.git
cd tfhe
cp path/to/patch_fft.patch ./
git apply patch_fft.patch
make
``` 


## Run the code

Once TFHElib version 1.1 and the provided patch are installed, you should:

```bash
Go to the newly created directory full-LUT.    
Update the path to the TFHElib directory in the provided sources/CMakeList.txt.     
In the full-LUT directory, run the "cmake -S . -B ./build" command.      
Run "cd build ; make" to finalize compilation.     
Command "../bin/aes" will then run our AES homomorphic evaluation.  
``` 

## Parallelization
To allow parallelization, you can change the value of the `NB_THREAD` variable line 6 of aes.cpp. It is set to 1 by default, so no parallelization is used.