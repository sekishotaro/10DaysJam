#include "SceneFactory.h"
#include "ResultScene.h"
#include "GamePlayScene.h"
#include "TitleScene.h"
#include "SelectScene.h"

BaseScene *SceneFactory::CreateScene(const std::string &sceneName)
{
    //次のシーンを作成
    BaseScene *newScene = nullptr;


    if (sceneName == "TITLE")
    {
        newScene = new TitleScene();
    }
    else if (sceneName == "GAMEPLAY")
    {
        newScene = new GamePlayScene();
    }
    else if (sceneName == "RESULT")
    {
        newScene = new ResultScene();
    }
    else if (sceneName == "SELECT")
    {
        newScene = new SelectScene();
    }
    return newScene;
}
