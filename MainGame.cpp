#include "pch.h"

/// 씬 인클루드
#include "Scene01_Intro.h"
#include "Scene03_Cut.h"
#include "Scene02_WorldChoice.h"
#include "Scene04_Stage.h"
#include "Scene05_Ingame.h"
#include "Scene06_Result.h"
#include "Scene_Loding.h"

//////////////////////////////
#include "MainGame.h"

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

HRESULT MainGame::Init(void)
{
	//upcasting : 부모클래스를 생성자 호출한다
	GameNode::Init(true);

	/// 디버깅 모드 설정
	g_debugMode = TRUE;

	/// 게임에서 사용할 이미지 추가
	LoadAllImage();

	/// 게임에서 사용할 사운드 추가
	LoadAllSound();

	/// 게임에서 사용할 씬 등록
	RegisterAllScene();

	/// 스타트씬 설정
	SCENEMANAGER->ChangeScene("_introScene");
	//SCENEMANAGER->ChangeScene("_stageScene");

	return S_OK;
}

void MainGame::Release(void)
{
	GameNode::Release();
}

void MainGame::Update(void)
{
	GameNode::Update();

	SCENEMANAGER->Update();
}

void MainGame::Render()
{
	DrawRect(g_backBuffer->GetMemDC(), 0, 0, BACKDCSIZEX, BACKDCSIZEY);
	//========================================================

	SCENEMANAGER->Render();

	//========================================================
	g_backBuffer->Render(GetMainDC(), 0, 0);
}

HRESULT MainGame::LoadAllImage()
{
	// 인트로
	IMAGEMANAGER->AddImage("INTRO", ConvertPath("Intro_new_title.bmp", 1), 1416, 1159, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("INTRO_PIXEL", ConvertPath("Intro_1.bmp", 1), 1416, 1159, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("INTRO_BLUR", ConvertPath("Intro_bg1.bmp", 1), 1416, 1159, true, RGB(255, 0, 255));

	// 월드 선택
	IMAGEMANAGER->AddImage("WORLD_CHOICE", ConvertPath("worldmap_map.bmp", 1), 1416, 1159, true, RGB(255, 0, 255));

	// 로딩
	IMAGEMANAGER->AddFrameImage("LODING", ConvertPath("Intro_new_patch.bmp", 1), 0, 0, 11328, 1159, 8, 1, true, RGB(255, 0, 255));

	// 스토리 컷 
	IMAGEMANAGER->AddImage("STORY_01", ConvertPath("story_1.bmp", 1), 1416, 1159, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("STORY_02", ConvertPath("story_2.bmp", 1), 0, 0, 21240, 1159, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("STORY_03", ConvertPath("story_3.bmp", 1), 1416, 1159, true, RGB(255, 0, 255));

	/// 인게임
	// 인게임 백그라운드 맵
	IMAGEMANAGER->AddImage("BG_MOUNTAIN", ConvertPath("BG_MOUNTAIN.bmp", 1), 2800, 2100, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("BG_INGAME", ConvertPath("BG04.bmp", 1), 2832, 2318, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("BG_INGAME02", ConvertPath("BG.bmp", 1), 2832, 2318, true, RGB(255, 0, 255));

	// 플레이어 애니메이션
	IMAGEMANAGER->AddFrameImage("PLAYER_MOVE_R", ConvertPath("1123_slime_R_MOVE.bmp", 1), 0, 0, 640, 140, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("PLAYER_MOVE_L", ConvertPath("1123_slime_L_MOVE.bmp", 1), 0, 0, 640, 140, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("PLAYER_JUMP_R", ConvertPath("1123_slime_Jump_R.bmp", 1), 0, 0, 1040, 140, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("PLAYER_JUMP_L", ConvertPath("1123_slime_Jump_L.bmp", 1), 0, 0, 1040, 140, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("PLAYER_FALL_R", ConvertPath("1123_slime_Fall_R.bmp", 1), 0, 0, 720, 140, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddFrameImage("PLAYER_FALL_L", ConvertPath("1123_slime_Fall_L.bmp", 1), 0, 0, 720, 140, 9, 1, true, RGB(255, 0, 255));

	// 열매 애니메이션
	IMAGEMANAGER->AddFrameImage("FRUIT", ConvertPath("fruit.bmp", 1), 0, 0, 2000, 300, 11, 1, true, RGB(255, 0, 255));

	/// 블럭 타일
	// 땅
	IMAGEMANAGER->AddImage("GRASS_01", ConvertPath("GrassTile_1.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("GRASS_02", ConvertPath("GrassTile_2.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("GRASS_03", ConvertPath("GrassTile_3.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	// 땅 비활성화 이미지
	IMAGEMANAGER->AddImage("GRASS_01_RED", ConvertPath("R_GrassTile_1.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("GRASS_02_RED", ConvertPath("R_GrassTile_2.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("GRASS_03_RED", ConvertPath("R_GrassTile_3.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));

	// 땅 둥근모서리
	IMAGEMANAGER->AddImage("GRASS_ROUND_L01", ConvertPath("GrassTile_L.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("GRASS_ROUND_L02", ConvertPath("GrassTile_L2.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("GRASS_ROUND_R01", ConvertPath("GrassTile_R.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("GRASS_ROUND_R02", ConvertPath("GrassTile_R2.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));

	// 땅 둥근모서리 비활성화 이미지
	IMAGEMANAGER->AddImage("GRASS_ROUND_L01_RED", ConvertPath("R_GrassTile_L.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("GRASS_ROUND_L02_RED", ConvertPath("R_GrassTile_L2.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("GRASS_ROUND_R01_RED", ConvertPath("R_GrassTile_R.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("GRASS_ROUND_R02_RED", ConvertPath("R_GrassTile_R2.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));

	// 땅 속
	IMAGEMANAGER->AddImage("GROUND_02", ConvertPath("Ground_2.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("GROUND_03", ConvertPath("Ground_3.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));

	// 땅 속 비활성화 이미지
	IMAGEMANAGER->AddImage("GROUND_02_RED", ConvertPath("R_ground_2.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("GROUND_03_RED", ConvertPath("R_ground_3.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));

	// 나무
	IMAGEMANAGER->AddImage("WOOD_TRUNK", ConvertPath("Block_trunk.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("WOOD_TRUNK_L", ConvertPath("Block_trunkend_L.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("WOOD_TRUNK_M", ConvertPath("Block_trunkend_M.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("WOOD_TRUNK_R", ConvertPath("Block_trunkend_R.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));

	IMAGEMANAGER->AddImage("WOOD_TRUNK_RED", ConvertPath("R_trunk.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("WOOD_TRUNK_L_RED", ConvertPath("R_trunkeach_L.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("WOOD_TRUNK_M_RED", ConvertPath("R_trunkeach_M.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("WOOD_TRUNK_R_RED", ConvertPath("R_trunkeach_R.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));

	// 풀
	IMAGEMANAGER->AddImage("BUSH_01", ConvertPath("wOOD_1.bmp", 1), 140, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("BUSH_02", ConvertPath("wOOD_2.bmp", 1), 140, 70, true, RGB(255, 0, 255));

	// 물
	IMAGEMANAGER->AddImage("WATER", ConvertPath("water.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("WATER_IN", ConvertPath("Uwater.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));

	IMAGEMANAGER->AddImage("WATER_RED", ConvertPath("R_water.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("WATER_IN_RED", ConvertPath("R_Uwater.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));

	// 돌
	IMAGEMANAGER->AddImage("ROCK_01", ConvertPath("Rock.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("ROCK_02", ConvertPath("Rock2.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));

	// 기믹
	IMAGEMANAGER->AddImage("DOOR_CLOSE", ConvertPath("door_close.bmp", 1), 140, 210, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DOOR_CLOSE_RED", ConvertPath("R_door_close.bmp", 1), 140, 210, true, RGB(255, 0, 255));

	IMAGEMANAGER->AddImage("DOOR_OPEN", ConvertPath("door_open.bmp", 1), 140, 210, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("DOOR_OPEN_RED", ConvertPath("R_door_open.bmp", 1), 140, 210, true, RGB(255, 0, 255));

	IMAGEMANAGER->AddImage("KEY", ConvertPath("key.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("KEY_RED", ConvertPath("R_key.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));

	IMAGEMANAGER->AddImage("SPRING", ConvertPath("spring.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("SPRING_RED", ConvertPath("R_spring.bmp", 1), TILESIZE, TILESIZE, true, RGB(255, 0, 255));

	/// UI 관련 이미지

	// 배경
	IMAGEMANAGER->AddImage("UI_BG_01", ConvertPath("Title.bmp", 1), 840, 140, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_BG_02", ConvertPath("UI1.bmp", 1), 1120, 490, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_BG_03", ConvertPath("UI_BG.bmp", 1), 1260, 910, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_BG_04", ConvertPath("UI_ingame01.bmp", 1), 1370, 200, true, RGB(255, 0, 255));

	// 버튼 문구
	IMAGEMANAGER->AddImage("UI_STAGE_TITLE", ConvertPath("Title01.bmp", 1), 840, 140, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_CLEAR_STAGE", ConvertPath("stageclear.bmp", 1), 840, 140, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_SELECT_STAGE", ConvertPath("select_stage.bmp", 1), 420, 140, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_WORLD_MAP", ConvertPath("worldmap_button.bmp", 1), 420, 140, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_NEW_SAVIOR", ConvertPath("Tiltle_botton.bmp", 1), 840, 140, true, RGB(255, 0, 255));

	// 버튼 모양
	IMAGEMANAGER->AddImage("UI_BUTTON", ConvertPath("button.bmp", 1), 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_BUTTON_GOBACK", ConvertPath("goBack.bmp", 1), 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_BUTTON_NEXTSTAGE", ConvertPath("nextStage.bmp", 1), 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_BUTTON_RESTART", ConvertPath("restart.bmp", 1), 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_BUTTON_RESET", ConvertPath("reset.bmp", 1), 100, 100, true, RGB(255, 0, 255));

	// 스테이지 창, 버튼 비활성화
	IMAGEMANAGER->AddImage("UI_STEMP_OFF_01", ConvertPath("stemp_B1.bmp", 1), 140, 210, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_STEMP_OFF_02", ConvertPath("stemp_B2.bmp", 1), 140, 210, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_STEMP_OFF_03", ConvertPath("stemp_B3.bmp", 1), 140, 210, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_STEMP_OFF_04", ConvertPath("stemp_B4.bmp", 1), 140, 210, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_STEMP_OFF_05", ConvertPath("stemp_B5.bmp", 1), 140, 210, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_STEMP_OFF_06", ConvertPath("stemp_B6.bmp", 1), 140, 210, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_STEMP_OFF_07", ConvertPath("stemp_B7.bmp", 1), 140, 210, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_STEMP_OFF_08", ConvertPath("stemp_B8.bmp", 1), 140, 210, true, RGB(255, 0, 255));

	// 스테이지 창, 버튼 활성화
	IMAGEMANAGER->AddImage("UI_STEMP_ON_01", ConvertPath("stemp1.bmp", 1), 140, 210, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_STEMP_ON_02", ConvertPath("stemp2.bmp", 1), 140, 210, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_STEMP_ON_03", ConvertPath("stemp3.bmp", 1), 140, 210, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_STEMP_ON_04", ConvertPath("stemp4.bmp", 1), 140, 210, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_STEMP_ON_05", ConvertPath("stemp5.bmp", 1), 140, 210, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_STEMP_ON_06", ConvertPath("stemp6.bmp", 1), 140, 210, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_STEMP_ON_07", ConvertPath("stemp7.bmp", 1), 140, 210, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_STEMP_ON_08", ConvertPath("stemp8.bmp", 1), 140, 210, true, RGB(255, 0, 255));

	// 결과창, 별
	IMAGEMANAGER->AddImage("UI_STAR_EMPTY", ConvertPath("star.bmp", 1), 280, 280, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_STAR_S", ConvertPath("star_S.bmp", 1), 280, 350, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_STAR_O", ConvertPath("star_O.bmp", 1), 280, 280, true, RGB(255, 0, 255));
	IMAGEMANAGER->AddImage("UI_STAR_P", ConvertPath("star_P.bmp", 1), 280, 350, true, RGB(255, 0, 255));

	return S_OK;
}

HRESULT MainGame::RegisterAllScene()
{
	// 인트로 씬
	_introScene = new Scene01_Intro;
	SCENEMANAGER->AddScene("_introScene", _introScene);

	// 컷 씬
	_cutScene = new Scene03_Cut;
	SCENEMANAGER->AddScene("_cutScene", _cutScene);

	// 월드 선택 씬
	_worldchoiceScene = new Scene02_WorldChoice;
	SCENEMANAGER->AddScene("_worldchoiceScene", _worldchoiceScene);

	// 스테이지 선택 씬
	_stageScene = new Scene04_Stage;
	SCENEMANAGER->AddScene("_stageScene", _stageScene);

	// 인게임 씬
	_ingameScene = new Scene05_Ingame;
	SCENEMANAGER->AddScene("_ingameScene", _ingameScene);

	// 결과창 씬
	_resultScene = new Scene06_Result;
	SCENEMANAGER->AddScene("_resultScene", _resultScene);

	// 로딩 씬
	_loadingScene = new Scene_Loding;
	SCENEMANAGER->AddScene("_lodingScene", _loadingScene);

	return S_OK;
}

HRESULT MainGame::LoadAllSound()
{
	SOUNDMANAGER->AddSound("BGM_WORLD", ConvertPath("Bgm_World.wav", 2));
	SOUNDMANAGER->AddSound("BGM_STORY", ConvertPath("Bgm_Story.wav", 2));

	SOUNDMANAGER->AddSound("BGM_STAGE", ConvertPath("Bgm_Stage.wav", 2));
	
	SOUNDMANAGER->AddSound("BGM_INGAME", ConvertPath("Bgm_Ingame.wav", 2));
	
	SOUNDMANAGER->AddSound("JUMP", ConvertPath("SFX_slime jump.wav", 2));
	SOUNDMANAGER->AddSound("SPRINGJUMP", ConvertPath("SFX_spring jump.wav", 2));
	SOUNDMANAGER->AddSound("DIE", ConvertPath("SFX_slime die.wav", 2));
	SOUNDMANAGER->AddSound("LAND", ConvertPath("SFX_slime_Land.wav", 2));
	
	SOUNDMANAGER->AddSound("BUTTON_CLICK", ConvertPath("SFX_buttonclick.wav", 2));
	
	SOUNDMANAGER->AddSound("BGM_CLEAR", ConvertPath("Bgm_clear.wav", 2));
	
	return S_OK;
}
