# Cats vs. Rats GBA Edition

Current project: Allow us to select and place multiple cats only if we can afford them.

See https://github.com/walkingeyerobot/pokeemerald/wiki/wsl2-and-vscode-setup for development environment info

Convention: under_score_everything  
noCamelCasePlease  
CONSTANTS_LIKE_THIS

* main  
    * timer manager  
    * screen manager  
        * main menu  
        * tilemap  
    * sprite manager  
        * keeps an array of sprites and a method to copy them to memory  
        * cat manager  
        * rat manager  
    * data