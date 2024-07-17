# Bot for croupier

#### 1. Preface:
The bot was created for training purposes for a small group of dealers.

#### 2. Who is the user of the bot?
Croupiers who need to train the betting count on the roulette track.

#### 3. What this bot does.
The bot inputs the roulette minimum, roulette maximum, the series being played and the bet on that series. then the bot asks how much the given series is playing, and then asks for change. the bot outputs the correct answer with the last message.

#### 4. Run
- In the main folder in the .env file, specify the bot token (see example.env)
- gcc -c -libcurl telegramm.c
- gcc -c json_parser.c
- gcc -c roulette.c
- gcc main.o telegramm.o json_parser.o roulette.o -lcurl -o main
- ./main
