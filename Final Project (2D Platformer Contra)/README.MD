# !IMPORTANT! MUST READ BEFORE INSTALLATION 

## How to run this project 

**Note: There is a lot of lag loading between levels and so running each level individually is the only option.**

* Download the files in this folder and run the assignment 1. 

### Running Menu & First Level

* Step 1: Go into "GameMode.cpp" file and change the initialization mode to STATE_TITLE_SCREEN. 
  
### Running Second Level (this level is not for those who get motion-sick easily)

* Step 1: Go into "GameMode.cpp" file and change the initialization mode to STATE_GAME_LEVEL_2. 
* Step 2: Go into "main.cpp" file and look for the setup function
  * Within setup function, if there is function call to "state.setup1("some_file_name.txt")"
    change some_file_name.txt to "Scene_2.txt".
    
    If there isn't the function call "state.setup("...")"  then create the function like this: 
    state.setup1("Scene_2.txt");
    
    Else, if the code already says "state.setup1("Scene_2.txt")", then leave as is. 
  
### Running Third Level

* Step 1: Go into "GameMode.cpp" file and change the initialization mode to STATE_GAME_LEVEL_3.
* Step 2: Do Step 2 from "Running Second Level" except with the parameter name as "Scene_3.txt"

