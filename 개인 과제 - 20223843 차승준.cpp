#include<bangtal.h>
#include<stdio.h>
#include <stdlib.h>
#include<time.h>

SceneID instructions, court;
ObjectID startbutton, endbutton, passbutton, shootbutton, restartbutton, redturn, blueturn, ball, blueteam1, blueteam2, blueteam3, blueteam4, blueteam5, redteam1, redteam2, redteam3, redteam4, redteam5;
TimerID timer1;

int bluescore = 99, redscore = 99;
int ballX = 612, ballY = 332;

void startGame() {
    hideObject(restartbutton);
    hideObject(endbutton);
    showObject(passbutton);
    showObject(shootbutton);
    startTimer(timer1);
    setTimer(timer1, 15.0f);
    hideObject(blueteam5);
    ballX = 330, ballY = 150;
    locateObject(ball, court, ballX, ballY);
}

void endGame(bool success) {
    if (success) {
        showMessage("승리하였다!!");

    }
    else {
        showMessage("승리하지 못하였다!!");
    }
    hideObject(passbutton);
    hideObject(shootbutton);
    hideObject(redturn);
    hideObject(blueturn);
    showObject(restartbutton);
    showObject(endbutton);
    showObject(blueteam5);
    stopTimer(timer1);
    ballX = 612, ballY = 332; 
    locateObject(ball, court, ballX, ballY);
    
}

void mousecallback(ObjectID object, int x, int y, MouseAction) {

    if (object == startbutton) {
        enterScene(court);
        timer1 = createTimer(15.0f);
        showTimer(timer1);
        startGame();
    }
    
    else if (object == endbutton) {
        endGame();
    }

    else if (object == restartbutton) {
        startGame();
    }

    else if (object == blueturn) {
        showObject(passbutton);
        showObject(shootbutton);
        hideObject(blueturn);
        ballX = 330, ballY = 150;
        hideObject(blueteam5);
        locateObject(ball, court, ballX, ballY);
    }
    
    else if (object == redturn) {
        srand(time(NULL));
        switch (rand() % 2) {
        case 0:
            ballX = 70, ballY = 330;
            locateObject(ball, court, ballX, ballY);
            showMessage("빨강팀 3득점!!");
            redscore = redscore + 3;
            break;
        case 1:
            ballX = 70, ballY = 450;
            locateObject(ball, court, ballX, ballY);
            showMessage("빨강팀 득점실패!!");
            break;
        
        }
        hideObject(redturn);
        showObject(blueturn);

    }

    else if (object == passbutton) {
        srand(time(NULL));
        switch (rand() % 4) {
        case 0:
            ballX = 750, ballY = 500;
            locateObject(ball, court, ballX, ballY);
            hideObject(blueteam1);
            showObject(blueteam2);
            showObject(blueteam3);
            showObject(blueteam4);
            showObject(blueteam5);
            break;
        case 1:
            ballX = 750, ballY = 120;
            locateObject(ball, court, ballX, ballY);
            hideObject(blueteam2);
            showObject(blueteam1);
            showObject(blueteam3);
            showObject(blueteam4);
            showObject(blueteam5);
            break;
        case 2:
            ballX = 1020, ballY = 310;
            locateObject(ball, court, ballX, ballY);
            hideObject(blueteam3);
            showObject(blueteam1);
            showObject(blueteam2);
            showObject(blueteam4);
            showObject(blueteam5);
            break;
        case 3:
            ballX = 200, ballY = 480;
            locateObject(ball, court, ballX, ballY);
            hideObject(blueteam4);
            showObject(blueteam1);
            showObject(blueteam2);
            showObject(blueteam3);
            showObject(blueteam5);
            break;
        }
        hideObject(passbutton);
    }
    else  if (object == shootbutton) {
    showObject(blueteam1);
    showObject(blueteam2);
    showObject(blueteam3);
    showObject(blueteam4);
    showObject(blueteam5);
        if (ballX < 640) {
            srand(time(NULL));
            switch (rand() % 4) {
              case 0:
                ballX = 1150, ballY = 320;
                locateObject(ball, court, ballX, ballY);
                showMessage("2득점!!");
                bluescore = bluescore + 2;
                break;
              case 1:
                ballX = 1150, ballY = 450;
                locateObject(ball, court, ballX, ballY);
                showMessage("득점실패!!");
                break;
              case 2:
                ballX = 1150, ballY = 200;
                locateObject(ball, court, ballX, ballY);
                showMessage("득점실패!!");
                break;
              case 3:
                ballX = 1150, ballY = 210;
                locateObject(ball, court, ballX, ballY);
                showMessage("득점실패!!");
                break;

            }
            hideObject(shootbutton);
            hideObject(passbutton);
            showObject(redturn);
            
        }
        if (ballX > 640) {
            srand(time(NULL));
            switch (rand() % 2) {
              case 0:
                ballX = 1150, ballY = 320;
                locateObject(ball, court, ballX, ballY);
                showMessage("2득점!!");
                bluescore = bluescore + 2;
                break;
              case 1:
                ballX = 1150, ballY = 450;
                locateObject(ball, court, ballX, ballY);
                showMessage("득점실패!!");
                break;

            }
            hideObject(shootbutton);
            hideObject(passbutton);
            showObject(redturn);

        }
    }
    
}

ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown) {
    ObjectID object = createObject(image);
    locateObject(object, scene, x, y);
    if (shown) {
        showObject(object);
    }
    return object;
}

void timerCallback(TimerID timer) {
    if (timer == timer1) {
        if (bluescore > redscore) {
            endGame(true);
        }
        else if (bluescore < redscore) {
            endGame(false);
        }
        else if (bluescore == redscore) {
            endGame(false);
        }
    }
}

int main() {
	
    setTimerCallback(timerCallback);
    setMouseCallback(mousecallback);

	court = createScene("코트", "images/court.png");
    instructions = createScene("안내서", "images/instructions.png");
	
    startbutton = createObject("images/start.png", instructions, 590, 70, true);
    endbutton = createObject("images/end.png", court, 590, 20, false);
    passbutton = createObject("images/passbutton.png", court, 590, 70, false);
    shootbutton = createObject("images/shootbutton.png", court, 590, 20, false);
    restartbutton = createObject("images/restart.png", court, 590, 70, false);
    ball = createObject("images/ball.png", court, ballX, ballY, true);
    redturn = createObject("images/redturn.png", court, 590, 70, false);
    blueturn = createObject("images/blueturn.png", court, 590, 70, false);

    blueteam1 = createObject("images/blueteam.png", court, 750, 500, true);
    blueteam2 = createObject("images/blueteam.png", court, 750, 120, true);
    blueteam3 = createObject("images/blueteam.png", court, 1020, 310, true);
    blueteam4 = createObject("images/blueteam.png", court, 200, 480, true);
    blueteam5 = createObject("images/blueteam.png", court, 330, 150, true);

    redteam1 = createObject("images/redteam.png", court, 750, 310, true);
    redteam2 = createObject("images/redteam.png", court, 930, 120, true);
    redteam3 = createObject("images/redteam.png", court, 1020, 480, true);
    redteam4 = createObject("images/redteam.png", court, 340, 480, true);
    redteam5 = createObject("images/redteam.png", court, 450, 300, true);

     
    

    setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	

    startGame(instructions);

}