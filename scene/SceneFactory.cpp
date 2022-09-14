#include "SceneFactory.h"
#include "ResultScene.h"
#include "GamePlayScene.h"
#include "TitleScene.h"
#include "SelectScene.h"

#include "GameStage_1.h"
#include "GameStage_2.h"
#include "GameStage_3.h"
#include "GameStage_4.h"
#include "GameStage_5.h"

#include "GameStage_6.h"
#include "GameStage_7.h"
#include "GameStage_8.h"
#include "GameStage_9.h"
#include "GameStage_10.h"

#include "GameOverScene.h"
BaseScene *SceneFactory::CreateScene(const std::string &sceneName)
{
    //éüÇÃÉVÅ[ÉìÇçÏê¨
    BaseScene *newScene = nullptr;


    if (sceneName == "TITLE")
    {
        newScene = new TitleScene();
    }
    else if (sceneName == "GAMEPLAY")
    {
        newScene = new GamePlayScene();
    }
    else if (sceneName == "STAGE_1")
    {
        newScene = new GameStage_1();
    }
    else if (sceneName == "STAGE_2")
    {
        newScene = new GameStage_2();
    }
    else if (sceneName == "STAGE_3")
    {
        newScene = new GameStage_3();
    }
    else if (sceneName == "STAGE_4")
    {
        newScene = new GameStage_4();
    }
    else if (sceneName == "STAGE_5")
    {
        newScene = new GameStage_5();
    }

    else if (sceneName == "STAGE_6")
    {
        newScene = new GameStage_6();
    }
    else if (sceneName == "STAGE_7")
    {
        newScene = new GameStage_7();
    }
    else if (sceneName == "STAGE_8")
    {
        newScene = new GameStage_8();
    }
    else if (sceneName == "STAGE_9")
    {
        newScene = new GameStage_9();
    }
    else if (sceneName == "STAGE_10")
    {
        newScene = new GameStage_10();
    }
    else if (sceneName == "RESULT")
    {
        newScene = new ResultScene();
    }
    else if (sceneName == "SELECT")
    {
        newScene = new SelectScene();
    }
    else if (sceneName == "GAMEOVER")
    {
        newScene = new GameOverScene();
    }
    return newScene;
}
