#include "pch.h"
#include "Player.h"
#include "Scene05_Ingame.h"



using namespace std;

// 스테이지 번호
int g_stageNum = 1;

// 카메라 리셋 플래그
bool g_editModeCameraReset = true;

Scene05_Ingame::Scene05_Ingame()
{
   _imgBg = nullptr;
   _imgBg02 = nullptr;
   _imgBg03 = nullptr;

   //문과 키
   _imgKey = nullptr;
   _imgDoorClose = nullptr;
   _imgDoorOpen = nullptr;
   _imgSpring = nullptr;

   _imgWood = nullptr;
   _imgWoodL = nullptr;
   _imgWoodM = nullptr;
   _imgWoodR = nullptr;

   _imgFruit = nullptr;

   _imgWater = nullptr;
   _imgUWater = nullptr;

   _imgGrass02 = nullptr;
   _imgGrass03 = nullptr;
   _imgGrassL = nullptr;
   _imgGrassL2 = nullptr;
   _imgGrassR = nullptr;
   _imgGrassR2 = nullptr;

   _imgUnderGround02 = nullptr;
   _imgUnderGround03 = nullptr;

   // (비활성) 빨강색 혼
   _imgWood_R = nullptr;
   _imgWoodL_R = nullptr;
   _imgWoodM_R = nullptr;
   _imgWoodR_R = nullptr;

   _imgGrass02_R = nullptr;
   _imgGrass03_R = nullptr;
   _imgGrassL_R = nullptr;
   _imgGrassL2_R = nullptr;
   _imgGrassR_R = nullptr;
   _imgGrassR2_R = nullptr;

   _imgUnderGround02_R = nullptr;
   _imgUnderGround03_R = nullptr;

   _imgWater_R = nullptr;
   _imgUWater_R = nullptr;

   _imgKey_R = nullptr;
   _imgDoorClose_R = nullptr;
   _imgDoorOpen_R = nullptr;
   _imgSpring_R = nullptr;

   // UI 이미지 
   _imgBackBoard = nullptr;
   _imgRestart = nullptr;
   _imgReset = nullptr;
   _imgGoBack = nullptr;
   _imgNextStage = nullptr;

   // 장식 풀, 돌 이미지
   _imgRock01 = nullptr;
   _imgRock02 = nullptr;
   _imgBush01 = nullptr;
   _imgBush02 = nullptr;
}

Scene05_Ingame::~Scene05_Ingame()
{

}

HRESULT Scene05_Ingame::Init(void)
{
   g_debugMode = false;

   // 초기화 시 마다 타이머를 0으로 리셋
   _timer = 0.0f;


   /// 이미지 연결
   // 백그라운드 이미지
   _imgBg = IMAGEMANAGER->FindImage("BG_MOUNTAIN");
   _imgBg02 = IMAGEMANAGER->FindImage("BG_INGAME");
   _imgBg03 = IMAGEMANAGER->FindImage("BG_INGAME02");

   //문과 키
   _imgKey = IMAGEMANAGER->FindImage("KEY");
   _imgDoorClose = IMAGEMANAGER->FindImage("DOOR_CLOSE");
   _imgDoorOpen = IMAGEMANAGER->FindImage("DOOR_OPEN");
   _imgSpring = IMAGEMANAGER->FindImage("SPRING");

   _imgWood = IMAGEMANAGER->FindImage("WOOD_TRUNK");
   _imgWoodL = IMAGEMANAGER->FindImage("WOOD_TRUNK_L");
   _imgWoodM = IMAGEMANAGER->FindImage("WOOD_TRUNK_M");
   _imgWoodR = IMAGEMANAGER->FindImage("WOOD_TRUNK_R");

   _imgFruit = IMAGEMANAGER->FindImage("FRUIT");

   _imgWater = IMAGEMANAGER->FindImage("WATER");
   _imgUWater = IMAGEMANAGER->FindImage("WATER_IN");

   _imgGrass02 = IMAGEMANAGER->FindImage("GRASS_02");
   _imgGrass03 = IMAGEMANAGER->FindImage("GRASS_03");
   _imgGrassL = IMAGEMANAGER->FindImage("GRASS_ROUND_L01");
   _imgGrassL2 = IMAGEMANAGER->FindImage("GRASS_ROUND_L02");
   _imgGrassR = IMAGEMANAGER->FindImage("GRASS_ROUND_R01");
   _imgGrassR2 = IMAGEMANAGER->FindImage("GRASS_ROUND_R02");

   _imgUnderGround02 = IMAGEMANAGER->FindImage("GROUND_02");
   _imgUnderGround03 = IMAGEMANAGER->FindImage("GROUND_03");

   // (비활성) 빨강색 혼합 이미지
   _imgWood_R = IMAGEMANAGER->FindImage("WOOD_TRUNK_RED");
   _imgWoodL_R = IMAGEMANAGER->FindImage("WOOD_TRUNK_L_RED");
   _imgWoodM_R = IMAGEMANAGER->FindImage("WOOD_TRUNK_M_RED");
   _imgWoodR_R = IMAGEMANAGER->FindImage("WOOD_TRUNK_R_RED");

   _imgGrass02_R = IMAGEMANAGER->FindImage("GRASS_02_RED");
   _imgGrass03_R = IMAGEMANAGER->FindImage("GRASS_03_RED");
   _imgGrassL_R = IMAGEMANAGER->FindImage("GRASS_ROUND_L01_RED");
   _imgGrassL2_R = IMAGEMANAGER->FindImage("GRASS_ROUND_L02_RED");
   _imgGrassR_R = IMAGEMANAGER->FindImage("GRASS_ROUND_R01_RED");
   _imgGrassR2_R = IMAGEMANAGER->FindImage("GRASS_ROUND_R02_RED");

   _imgUnderGround02_R = IMAGEMANAGER->FindImage("GROUND_02_RED");
   _imgUnderGround03_R = IMAGEMANAGER->FindImage("GROUND_03_RED");

   _imgWater_R = IMAGEMANAGER->FindImage("WATER_RED");
   _imgUWater_R = IMAGEMANAGER->FindImage("WATER_IN_RED");

   _imgKey_R = IMAGEMANAGER->FindImage("KEY_RED");				// 키
   _imgDoorClose_R = IMAGEMANAGER->FindImage("DOOR_CLOSE_RED");		// 열린 문
   _imgDoorOpen_R = IMAGEMANAGER->FindImage("DOOR_OPEN_RED");			// 닫힌 문
   _imgSpring_R = IMAGEMANAGER->FindImage("SPRING_RED");

   // UI 이미지 
   _imgBackBoard = IMAGEMANAGER->FindImage("UI_BG_04");
   _imgRestart = IMAGEMANAGER->FindImage("UI_BUTTON_RESTART");
   _imgReset = IMAGEMANAGER->FindImage("UI_BUTTON_RESET");
   _imgGoBack = IMAGEMANAGER->FindImage("UI_BUTTON_GOBACK");
   _imgNextStage = IMAGEMANAGER->FindImage("UI_BUTTON_NEXTSTAGE");
   // 장식 풀, 돌 이미지
   _imgRock01 = IMAGEMANAGER->FindImage("ROCK_01");
   _imgRock02 = IMAGEMANAGER->FindImage("ROCK_02");
   _imgBush01 = IMAGEMANAGER->FindImage("BUSH_01");
   _imgBush02 = IMAGEMANAGER->FindImage("BUSH_02");

   /// 사운드 연결
   // 인게임 bgm 반복 재생
   _sndBG = SOUNDMANAGER->FindSound("BGM_INGAME");		// bgm 연결
   _sndBG->soundSeek(0);
   _sndBG->soundPlayLooping();

   /// Die 사운드
   _sndDie = SOUNDMANAGER->FindSound("DIE");

   /// 버튼 클릭 사운드(현재 오류로 사용하지 않음)
   _sndBtnClick = SOUNDMANAGER->FindSound("BUTTON_CLICK");

   /// 맵 초기화
   if (!m_pMap)
   {
      m_pMap = new Map();
      m_pMap->Initialize();
   }

   /// 플레이어 초기화
   if (!m_pPlayer)
   {
      m_pPlayer = new Player;
   }

   m_CameraX = m_pPlayer->m_PosX - (WINSIZEX / 2);
   m_CameraY = m_pPlayer->m_PosY - (WINSIZEY / 2);

   // 스테이지 번호에 맞춰서 맵 세팅
   switch (g_stageNum)
   {
      case 0:
         cout << "샘플 스테이지(0) Init\n\n";
         Init_Stage_Sample();
         break;

      case 1:
         cout << "스테이지 01 Init\n\n";
         Init_Stage01();
         break;

      case 2:
         cout << "스테이지 02 Init\n\n";
         Init_Stage02();
         break;

      case 3:
         cout << "스테이지 03 Init\n\n";
         Init_Stage03();
         break;
   }

   m_pPlayer->PlayerGravity();
   m_pPlayer->m_JumpPower = 0.0f;
   m_pPlayer->m_PlayerState = ONFLOOR;


   return S_OK;
}

void Scene05_Ingame::Init_Stage_Sample()
{
   InputBoardData(0);

   /// 배열의 원소 번호를 기준으로 좌표를 얻어서 캐릭터의 시작 위치를 잡는 방법
   // 캐릭터의 시작 타일 구하기
   //POINT pos = CalcCharSetPos(8, MAPSIZE_Y - 9);
   //_startPosX = pos.x;
   //_startPosY = pos.y;
   ///

   /// 배열에 있는 값(원소) 중에 첫 -1을 찾아서 플레이어의 시작위치를 잡는 방법
   for (int y = 0; y < MAPSIZE_Y; y++)
   {
      for (int x = 0; x < MAPSIZE_X; x++)
      {
         if (m_pMap->GetType(x, y) == Block::CHAR_START_POS)
         {
            m_StartPosX = x * TILESIZE;
            m_StartPosY = (y * TILESIZE) - TILESIZE; // y좌표는 한칸 보전해줘야 한다.

            break;
         }
      }
   }

   // 시작위치로 설정
   m_pPlayer->Initialize(TILESIZE, m_StartPosX, m_StartPosY);

   // 키는 안가진 상태로 항상 초기화
   m_pPlayer->m_IsPlayerGotKey = FALSE;

   // 오른쪽 이동 이미지로 세팅
   m_pPlayer->_img = IMAGEMANAGER->FindImage("PLAYER_MOVE_R");

   printf_s("캐릭터 위치[%f,%f] \n\n", m_pPlayer->m_PosX, m_pPlayer->m_PosY);

   /// 순서 중요

   // 카메라 위치 세팅
   MoveCamera();

   // 인게임 마우스 좌표 세팅
   MappingMousePoint();

   MappingUI();

   _gameState = Game_State::Edit;
}

void Scene05_Ingame::Init_Stage01()
{
   InputBoardData(1);
   SetLimitTime();

   /// 배열의 원소 번호를 기준으로 좌표를 얻어서 캐릭터의 시작 위치를 잡는 방법
   // 캐릭터의 시작 타일 구하기
   //POINT pos = CalcCharSetPos(8, MAPSIZE_Y - 9);
   //_startPosX = pos.x;
   //_startPosY = pos.y;
   ///

   /// 배열에 있는 값(원소) 중에 첫 -1을 찾아서 플레이어의 시작위치를 잡는 방법
   for (int y = 0; y < MAPSIZE_Y; y++)
   {
      for (int x = 0; x < MAPSIZE_X; x++)
      {
         if (m_pMap->GetType(x, y) == Block::CHAR_START_POS)
         {
            m_StartPosX = x * TILESIZE;
            m_StartPosY = (y * TILESIZE) - TILESIZE; // y좌표는 한칸 보전해줘야 한다.

            break;
         }
      }
   }

   // 시작위치로 설정
   m_pPlayer->Initialize(TILESIZE, m_StartPosX, m_StartPosY);
   m_pPlayer->m_XDirection = 1;

   // 키는 안가진 상태로 항상 초기화
   m_pPlayer->m_IsPlayerGotKey = FALSE;

   // 오른쪽 이동 이미지로 세팅
   m_pPlayer->_img = IMAGEMANAGER->FindImage("PLAYER_MOVE_R");

   printf_s("캐릭터 위치[%f,%f] \n\n", m_pPlayer->m_PosX, m_pPlayer->m_PosY);

   /// 순서 중요

   // 카메라 위치 세팅
   MoveCamera();

   // 인게임 마우스 좌표 세팅
   MappingMousePoint();

   // UI 좌표 설정
   MappingUI();

   // 시작시에 배치모드로 설정
   _gameState = Game_State::Edit;
}

void Scene05_Ingame::Init_Stage02()
{
   InputBoardData(2);
   SetLimitTime();

   /// 배열의 원소 번호를 기준으로 좌표를 얻어서 캐릭터의 시작 위치를 잡는 방법
   // 캐릭터의 시작 타일 구하기
   //POINT pos = CalcCharSetPos(8, MAPSIZE_Y - 9);
   //_startPosX = pos.x;
   //_startPosY = pos.y;
   ///

   /// 배열에 있는 값(원소) 중에 첫 -1을 찾아서 플레이어의 시작위치를 잡는 방법
   for (int y = 0; y < MAPSIZE_Y; y++)
   {
      for (int x = 0; x < MAPSIZE_X; x++)
      {
         if (m_pMap->GetType(x, y) == Block::CHAR_START_POS)
         {
            m_StartPosX = x * TILESIZE;
            m_StartPosY = (y * TILESIZE) - TILESIZE; // y좌표는 한칸 보전해줘야 한다.

            break;
         }
      }
   }

   // 시작위치로 설정
   m_pPlayer->Initialize(TILESIZE, m_StartPosX, m_StartPosY);
   m_pPlayer->m_XDirection = 1;

   // 키는 안가진 상태로 항상 초기화
   m_pPlayer->m_IsPlayerGotKey = FALSE;

   // 오른쪽 이동 이미지로 세팅
   m_pPlayer->_img = IMAGEMANAGER->FindImage("PLAYER_MOVE_R");

   printf_s("캐릭터 위치[%f,%f] \n\n", m_pPlayer->m_PosX, m_pPlayer->m_PosY);

   /// 순서 중요

   // 카메라 위치 세팅
   MoveCamera();

   // 인게임 마우스 좌표 세팅
   MappingMousePoint();

   // UI 좌표 설정
   MappingUI();

   // 시작시에 배치모드로 설정
   _gameState = Game_State::Edit;
}

void Scene05_Ingame::Init_Stage03()
{
   InputBoardData(3);
   SetLimitTime();

   /// 배열의 원소 번호를 기준으로 좌표를 얻어서 캐릭터의 시작 위치를 잡는 방법
   // 캐릭터의 시작 타일 구하기
   //POINT pos = CalcCharSetPos(8, MAPSIZE_Y - 9);
   //_startPosX = pos.x;
   //_startPosY = pos.y;
   ///

   /// 배열에 있는 값(원소) 중에 첫 -1을 찾아서 플레이어의 시작위치를 잡는 방법
   for (int y = 0; y < MAPSIZE_Y; y++)
   {
      for (int x = 0; x < MAPSIZE_X; x++)
      {
         if (m_pMap->GetType(x, y) == Block::CHAR_START_POS)
         {
            m_StartPosX = x * TILESIZE;
            m_StartPosY = (y * TILESIZE) - TILESIZE; // y좌표는 한칸 보전해줘야 한다.

            cout << y << "  " << x << "\n\n";

            break;
         }

      }
   }

   // 시작위치로 설정
   m_pPlayer->Initialize(TILESIZE, m_StartPosX, m_StartPosY);
   m_pPlayer->m_XDirection = 1;

   // 키는 안가진 상태로 항상 초기화
   m_pPlayer->m_IsPlayerGotKey = FALSE;

   // 오른쪽 이동 이미지로 세팅
   m_pPlayer->_img = IMAGEMANAGER->FindImage("PLAYER_MOVE_R");

   printf_s("캐릭터 위치[%f,%f] \n\n", m_pPlayer->m_PosX, m_pPlayer->m_PosY);

   /// 순서 중요

   // 카메라 위치 세팅
   MoveCamera();

   // 인게임 마우스 좌표 세팅
   MappingMousePoint();

   // UI 좌표 설정
   MappingUI();

   // 시작시에 배치모드로 설정
   _gameState = Game_State::Edit;
}

void Scene05_Ingame::Release(void)
{
   SAFE_DELETE(m_pPlayer);
   SAFE_DELETE(m_pMap);
}

void Scene05_Ingame::Update(void)
{
   /// 메인 스크린(DC)에 보여지게될 영역 조정(카메라 이동)
   MoveCamera();

   /// 실제 위치와 윈도우(창) 사이에 생기는 좌표 오차 조정
   MappingMousePoint();
   MappingUI();

   /// 디버깅 키 입력
   /// 속도, 점프력, 방향 전환 리셋 등..
   DebugingKeyInput();

   switch (_gameState)
   {
      /// 플레이 모드
      case Game_State::Play:
      {
         /// 타이머
         _timer += TIMEMANAGER->GetElaspedTimeSec();

         // 혹시 이전에 선택중이였다면 선택해제한다
         m_IsSelectMode = false;
         m_PickedBlockType = Block::BLOCK_MOUSEEMPTY;

         if (IsChangeMode())
         {
            g_editModeCameraReset = true;

            m_pPlayer->PlayerGravity();
            m_pPlayer->m_JumpPower = 0.0f;
            m_pPlayer->m_PlayerState = ONFLOOR;

            // 모드가 바뀌었으면 리턴하고 다시 프레임을 돌린다
            return;
         }

         if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
         {
            DebugShowMouseClickState();
            CheckCurrentBoard(m_ptMouse.x, m_ptMouse.y);
         }

         m_pPlayer->GetMapInfo(m_pMap);

         // 맵 영역 이탈 감지
         CheckPlayerPos(m_pPlayer->m_PosX, m_pPlayer->m_PosY);

         m_pPlayer->PlayerAutoMove();

         CheckStageClear();

         m_pPlayer->PlayerGravity();

         m_pPlayer->PlayerCheckUpTile(m_pMap);

         m_pPlayer->PlayerCheckSpring(m_pMap);

         m_pPlayer->PlayerCheckEmptyFloor(m_pMap);

         m_pPlayer->PlayerCheckFloor(m_pMap);

         m_pPlayer->PlayerCheckKey(m_pMap);

         m_pPlayer->PlayerCheckDoor(m_pMap);

         m_pPlayer->PlayerCheckWall(m_pMap);

         m_pPlayer->PlayerCheckRoof(m_pMap);

         break;
      }

      case Game_State::Edit:
      {
         // 에디트 -> 플레이
         if (IsChangeMode())
         {
            /// 타이머 리셋
            _timer = 0.0f;

            /// 캐릭터 위치 조정
            m_pPlayer->m_XDirection = 1;
            m_pPlayer->m_PosX = m_StartPosX;
            m_pPlayer->m_PosY = m_StartPosY;
            /// 오른쪽 이동 이미지로 세팅
            m_pPlayer->_img = IMAGEMANAGER->FindImage("PLAYER_MOVE_R");

            g_editModeCameraReset = false;

            m_pPlayer->m_IsPlayerGotKey = FALSE;

            m_pPlayer->m_PlayerState = ONFLOOR;


            for (int y = 0; y < MAPSIZE_Y; y++)
            {
               for (int x = 0; x < MAPSIZE_X; x++)
               {
                  if (g_stageNum == 2)
                  {
                     // 스테이지 02의 데이터에서 열쇠를 찾아서 시작 위치를 찾음
                     if (m_StageTwoData[y][x] == (int)Block::BLOCK_KEY)
                     {
                        m_KeyStartX = x;
                        m_KeyStartY = y;

                        m_pMap->SetType(m_KeyStartX, m_KeyStartY, Block::BLOCK_KEY);

                        break;
                     }

                     if (m_StageTwoData[y][x] == (int)Block::BLOCK_DOOR_CLOSE)
                     {

                        // 가로(2) * 세로(3) 칸에 닫힌 (문) 블록을 넣는다.
                        m_pMap->SetType(m_DoorStartX + 0, m_DoorStartY + 0, Block::BLOCK_DOOR_CLOSE);
                        m_pMap->SetType(m_DoorStartX + 1, m_DoorStartY + 0, Block::BLOCK_DOOR_CLOSE);
                        m_pMap->SetType(m_DoorStartX + 0, m_DoorStartY + 1, Block::BLOCK_DOOR_CLOSE);
                        m_pMap->SetType(m_DoorStartX + 1, m_DoorStartY + 1, Block::BLOCK_DOOR_CLOSE);
                        m_pMap->SetType(m_DoorStartX + 0, m_DoorStartY + 2, Block::BLOCK_DOOR_CLOSE);
                        m_pMap->SetType(m_DoorStartX + 1, m_DoorStartY + 2, Block::BLOCK_DOOR_CLOSE);

                        break;
                     }
                  }
               }
            }

            // 모드가 바뀌었으면 리턴하고 다시 프레임을 돌린다
            return;
         }

         // 마우스 왼 클릭이 됐으면
         if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
         {
            cout << "마우스 왼클릭 \n\n";
            SelectButton();
         }

         // 마우스 오른클릭 하면
         if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON))
         {
            // 선택 해제
            cout << "마우스 오른클릭 \n\n";
            m_PickedBlockType = Block::BLOCK_MOUSEEMPTY;
            m_IsSelectMode = false;
         }

         break;
      }

      case Game_State::Stop:
      {
         /// 타이머에 따른 클리어레벨 설정 
         SetClearLevel();

         cout << "스테이지 클리어. 클리어 레벨 = " << g_clearLevel << "\n\n";

         /// 사운드 재생 종료 (현재 버튼 사운드 오류 있음)
         _sndBG->soundPause();

         SCENEMANAGER->ChangeScene("_resultScene");
         return;
      }
   }// end of switch
}

void Scene05_Ingame::Render()
{
   // 배경을 먼저 그린다.
   //_imgBg->Render(g_backBuffer->GetMemDC(), 0, 0);
   _imgBg02->Render(g_backBuffer->GetMemDC(), 0, 0);
   //_imgBg03->Render(g_backBuffer->GetMemDC(), 0, 0);


   // 플레이어를 그린다.(프레임 애니메이션)
   m_pPlayer->_img->FrameRender(g_backBuffer->GetMemDC(), m_pPlayer->m_PosX, m_pPlayer->m_PosY);

   // 타일(블록)을 그린다.
   RenderTile();

   // 배치모드 UI 렌더
   if (_gameState == Game_State::Edit)
   {
      //. 라인 격자 그리기
      m_pMap->DrawGrid();

      RenderUI();
   }

   // 디버그 모드가 켜져 있으면 
   if (g_debugMode)
   {
      DebugShowInfo();
      m_pMap->DrawGrid();
      DebugDrawPlayerCollisionBox();
   }

   if (m_IsSelectMode)
   {
      switch (m_PickedBlockType)
      {
         // 1칸 블록을 선택 중일 때
         case Block::BLOCK_WOOD:
         {
            _imgWood->Render(g_backBuffer->GetMemDC(), m_ptMouse.x - TILESIZE / 2, m_ptMouse.y - TILESIZE / 2);
            break;
         }

         // 5칸 블록을 선택 중일 때
         case Block::BLOCK_WOOD_L:
         {
            if (g_stageNum == 1 || g_stageNum == 0)
            {
               _imgWoodL->Render(g_backBuffer->GetMemDC(), m_ptMouse.x - TILESIZE / 2 + TILESIZE * 0, m_ptMouse.y - TILESIZE / 2);
               _imgWoodM->Render(g_backBuffer->GetMemDC(), m_ptMouse.x - TILESIZE / 2 + TILESIZE * 1, m_ptMouse.y - TILESIZE / 2);
               _imgWoodM->Render(g_backBuffer->GetMemDC(), m_ptMouse.x - TILESIZE / 2 + TILESIZE * 2, m_ptMouse.y - TILESIZE / 2);
               _imgWoodM->Render(g_backBuffer->GetMemDC(), m_ptMouse.x - TILESIZE / 2 + TILESIZE * 3, m_ptMouse.y - TILESIZE / 2);
               _imgWoodR->Render(g_backBuffer->GetMemDC(), m_ptMouse.x - TILESIZE / 2 + TILESIZE * 4, m_ptMouse.y - TILESIZE / 2);
            }

            else
            {
               _imgWoodL->Render(g_backBuffer->GetMemDC(), m_ptMouse.x - TILESIZE / 2 + TILESIZE * 0, m_ptMouse.y - TILESIZE / 2);
               _imgWoodM->Render(g_backBuffer->GetMemDC(), m_ptMouse.x - TILESIZE / 2 + TILESIZE * 1, m_ptMouse.y - TILESIZE / 2);
               _imgWoodR->Render(g_backBuffer->GetMemDC(), m_ptMouse.x - TILESIZE / 2 + TILESIZE * 2, m_ptMouse.y - TILESIZE / 2);
            }

            break;
         }

         // 스프링 블록을 선택 중일 때
         case Block::BLOCK_SPRING:
         {
            _imgSpring->Render(g_backBuffer->GetMemDC(), m_ptMouse.x - TILESIZE / 2, m_ptMouse.y - TILESIZE / 2);
            break;
         }

      }// end of switch
   } // end of if

   // 카메라 렌더
   g_backBuffer->Render(g_backBuffer->GetMemDC(), 0, 0, m_CameraX, m_CameraY, BACKDCSIZEX, BACKDCSIZEY);
}

void Scene05_Ingame::InputBoardData(int mapData)
{
   switch (mapData)
   {
      /// 디자인용 샘플 맵 초기화
      case 0:
      {
         for (int y = 0; y < MAPSIZE_Y; y++)
         {
            for (int x = 0; x < MAPSIZE_X; x++)
            {
               m_pMap->SetType(x, y, (Block)m_SampleData[y][x]);
            }
         }

         break;
      }

      /// 스테이지 1 세팅
      case 1:
      {
         for (int y = 0; y < MAPSIZE_Y; y++)
         {
            for (int x = 0; x < MAPSIZE_X; x++)
            {
               m_pMap->SetType(x, y, (Block)m_StageOneData[y][x]);
            }
         }

         break;
      }

      /// 스테이지 2 세팅
      case 2:
      {
         for (int y = 0; y < MAPSIZE_Y; y++)
         {
            for (int x = 0; x < MAPSIZE_X; x++)
            {
               m_pMap->SetType(x, y, (Block)m_StageTwoData[y][x]);
            }
         }

         break;
      }

      /// 스테이지 3 세팅
      case 3:
      {
         for (int y = 0; y < MAPSIZE_Y; y++)
         {
            for (int x = 0; x < MAPSIZE_X; x++)
            {
               m_pMap->SetType(x, y, (Block)m_StageThreeData[y][x]);
            }
         }

         break;
      }
   }
}

void Scene05_Ingame::MoveCamera()
{
   //  플레이 모드에선 캐릭터 위치에 따라 자동 이동
   if (_gameState == Game_State::Play)
   {
      // 카메라 좌표 설정
      m_CameraX = m_pPlayer->m_PosX - (WINSIZEX / 2);
      m_CameraY = m_pPlayer->m_PosY - (WINSIZEY / 2);

      // ********* 카메라가 맵을 벗어나지 않도록 위치 조정 **********************

      // 캐릭터가 왼쪽 끝에 가까워져 카메라가 왼쪽으로 이동하면 안될 때
      if (m_pPlayer->m_PosX - WINSIZEX / 2 <= 0) m_CameraX = 0;

      // 캐릭터가 위쪽 끝에 가까워져 카메라가 위쪽으로 이동하면 안될 때
      if (m_pPlayer->m_PosY - WINSIZEY / 2 <= 0) m_CameraY = 0;

      // 캐릭터가 오른쪽 끝에 가까워져 카메라가 오른쪽으로 이동하면 안될 때
      //if (_player->m_PosX + WINSIZEX / 2 > _imgBg->GetWidth()) _cameraX = _imgBg->GetWidth() - WINSIZEX;
      if (m_pPlayer->m_PosX + WINSIZEX / 2 > 2800) m_CameraX = 2800 - WINSIZEX;

      // 캐릭터가 아래쪽 끝에 가까워져 카메라가 아래쪽으로 이동하면 안될 때
      if (m_pPlayer->m_PosY + WINSIZEY / 2 > _imgBg->GetHeight()) m_CameraY = _imgBg->GetHeight() - WINSIZEY;
   }

   // 배치모드에서 WASD 키 입력시 카메라 이동
   if (_gameState == Game_State::Edit)
   {
      if (!g_editModeCameraReset)
      {
         m_CameraX = m_pPlayer->m_PosX - (WINSIZEX / 2);
         m_CameraY = m_pPlayer->m_PosY - (WINSIZEY / 2);

         g_editModeCameraReset = true;
      }

      if (KEYMANAGER->IsStayKeyDown('W'))
      {
         m_CameraY -= 20.0f;
      }

      if (KEYMANAGER->IsStayKeyDown('S'))
      {
         m_CameraY += 20.0f;
      }

      if (KEYMANAGER->IsStayKeyDown('A'))
      {
         m_CameraX -= 20.0f;
      }

      if (KEYMANAGER->IsStayKeyDown('D'))
      {
         m_CameraX += 20.0f;
      }

      if (m_CameraX <= 0) m_CameraX = 0;
      if (m_CameraY <= 0) m_CameraY = 0;

      if (m_CameraX + WINSIZEX > _imgBg->GetWidth()) m_CameraX = _imgBg->GetWidth() - WINSIZEX;
      if (m_CameraY + WINSIZEY > _imgBg->GetHeight()) m_CameraY = _imgBg->GetHeight() - WINSIZEY;
   }
}

void Scene05_Ingame::MappingMousePoint()
{
   m_ptMouse.x = g_ptMouse.x + m_CameraX;
   m_ptMouse.y = g_ptMouse.y + m_CameraY;
}

void Scene05_Ingame::MappingUI()
{
   // 공통 UI 및 버튼 세팅
   _imgBackBoard->SetX(m_CameraX + 20);
   _imgBackBoard->SetY(m_CameraY + WINSIZEY - 250);

   _imgReset->SetX(m_CameraX + WINSIZEX - 130);
   _imgReset->SetY(_imgBackBoard->GetY() - 100);

   _imgGoBack->SetX(m_CameraX + 20);
   _imgGoBack->SetY(_imgBackBoard->GetY() - 100);


   /// 먼저 버튼들의 위치를 리셋 한다.
   // 1칸 나무
   _imgWood->SetX(0);
   _imgWood->SetY(-70);

   // 5 칸 나무(왼)
   _imgWoodL->SetX(0);
   _imgWoodL->SetY(-70);

   // 5 칸 나무(중간)
   _imgWoodM->SetX(0);
   _imgWoodM->SetY(-70);

   // 5 칸 나무(오)
   _imgWoodR->SetX(0);
   _imgWoodR->SetY(-70);

   // 스프링
   _imgSpring->SetX(0);
   _imgSpring->SetY(-70);

   // 키
   _imgKey->SetX(0);
   _imgKey->SetY(-70);

   // 닫힌 문
   _imgDoorClose->SetX(0);
   _imgDoorClose->SetY(-70);

   switch (g_stageNum)
   {
      // 디자인 용 샘플 맵의 버튼 세팅
      case 0:
         _imgWood->SetX(m_CameraX + 70);
         _imgWood->SetY(m_CameraY + 980);

         _imgWoodL->SetX(m_CameraX + 300);
         _imgWoodL->SetY(m_CameraY + 980);

         _imgWoodM->SetX(m_CameraX + 370);
         _imgWoodM->SetY(m_CameraY + 980);

         _imgWoodR->SetX(m_CameraX + 570);
         _imgWoodR->SetY(m_CameraY + 980);

         _imgSpring->SetX(m_CameraX + 700);
         _imgSpring->SetY(m_CameraY + 980);

         _imgKey->SetX(m_CameraX + 850);
         _imgKey->SetY(m_CameraY + 980);

         _imgDoorClose->SetX(m_CameraX + 1000);
         _imgDoorClose->SetY(m_CameraY + 890);
         break;

         // 스테이지 01 버튼 세팅
      case 1:
         _imgWood->SetX(m_CameraX + 420);
         _imgWood->SetY(m_CameraY + 980);

         _imgWoodL->SetX(m_CameraX + 700);
         _imgWoodL->SetY(m_CameraY + 980);

         _imgWoodM->SetX(_imgWoodL->GetX() + 70);
         _imgWoodM->SetY(m_CameraY + 980);


         _imgWoodR->SetX(_imgWoodM->GetX() + 200);
         _imgWoodR->SetY(m_CameraY + 980);

         break;

      case 2:
         _imgWood->SetX(m_CameraX + 420);
         _imgWood->SetY(m_CameraY + 980);

         _imgWoodL->SetX(m_CameraX + 800);
         _imgWoodL->SetY(m_CameraY + 980);

         _imgWoodM->SetX(_imgWoodL->GetX() + TILESIZE);
         _imgWoodM->SetY(_imgWoodL->GetY());

         _imgWoodR->SetX(_imgWoodM->GetX() + TILESIZE);
         _imgWoodR->SetY(_imgWoodM->GetY());

         break;

      case 3:
         _imgSpring->SetX(m_CameraX + 420);
         _imgSpring->SetY(m_CameraY + 980);

         _imgWoodL->SetX(m_CameraX + 800);
         _imgWoodL->SetY(m_CameraY + 980);

         _imgWoodM->SetX(_imgWoodL->GetX() + TILESIZE);
         _imgWoodM->SetY(_imgWoodL->GetY());

         _imgWoodR->SetX(_imgWoodM->GetX() + TILESIZE);
         _imgWoodR->SetY(_imgWoodM->GetY());
         break;
   }
}

// 배열원소 0번부터 size-1 의 좌표로 입력하시오.
// 0 ~ MAPSIZE - 1
bool Scene05_Ingame::CheckPlayerPos(float x, float y)
{
   int PlayerPosX = m_pPlayer->m_PosX + TILESIZE / 2;				// 중심 좌표
   int PlayerPosY = m_pPlayer->m_PosY + TILESIZE + TILESIZE / 2; // 캐릭터가 타일 사이즈 기준 1*2 사이즈라(70px,140px) y를 보정해 줌

   // 맵 왼쪽에 닿았을 때 방향 전환
   if (PlayerPosX < 0)
   {
      // 방향을 바꾸고 싶다면 여기를
      m_pPlayer->ChangeDirection();

      // 캐릭터의 위치를 리셋하고 다시 플레이하려면 여기를
      //this->ResetCharPos();
   }

   // 맵 위로 뚫고 올라갈 떄 아래로 보정한다.
   if (PlayerPosY < (0 + 200))
   {
      m_pPlayer->m_PosY += TILESIZE;
   }
   // 맵 오른쪽에 닿았을 때 
   if (PlayerPosX > (MAPSIZE_X * TILESIZE - TILESIZE / 2))
   {
      // 방향전환
      m_pPlayer->ChangeDirection();
   }

   if (PlayerPosY > (MAPSIZE_Y * TILESIZE - (TILESIZE * 5)))
   {
      this->ResetCharPos();
   }

   return false;
}

void Scene05_Ingame::ResetCharPos()
{
   bool findDoorStartPos = false;

   for (int y = 0; y < MAPSIZE_Y; y++)
   {
      for (int x = 0; x < MAPSIZE_X; x++)
      {
         // 먼저 문을 제거해준다
         if (m_pMap->m_pGameBoard[y][x]->m_Type == Block::BLOCK_DOOR_OPEN ||
            m_pMap->m_pGameBoard[y][x]->m_Type == Block::BLOCK_DOOR_CLOSE)
         {
            //m_pMap->m_pGameBoard[y][x]->m_Type = Block::BLOCK_EMPTY;
         }

         if (g_stageNum == 2)
         {
            // 스테이지 02의 데이터에서 열쇠를 찾아서 시작 위치를 찾음
            if (m_StageTwoData[y][x] == (int)Block::BLOCK_KEY)
            {
               m_KeyStartX = x;
               m_KeyStartY = y;

               m_pMap->SetType(m_KeyStartX, m_KeyStartY, Block::BLOCK_KEY);

               break;
            }

            // 스테이지 02의 데이터에서 닫힌 문의 위치를 찾아서 세팅한다
            if (m_StageTwoData[y][x] == (int)Block::BLOCK_DOOR_CLOSE && findDoorStartPos == false)
            {
               m_DoorStartX = x;
               m_DoorStartY = y;
               cout << "첫 도어 그리드 X = " << m_DoorStartX << " Y= " << m_DoorStartY << endl;

               // 가로(2) * 세로(3) 칸에 닫힌 (문) 블록을 넣는다.
               m_pMap->SetType(m_DoorStartX + 0, m_DoorStartY + 0, Block::BLOCK_DOOR_CLOSE);
               m_pMap->SetType(m_DoorStartX + 1, m_DoorStartY + 0, Block::BLOCK_DOOR_CLOSE);
               m_pMap->SetType(m_DoorStartX + 0, m_DoorStartY + 1, Block::BLOCK_DOOR_CLOSE);
               m_pMap->SetType(m_DoorStartX + 1, m_DoorStartY + 1, Block::BLOCK_DOOR_CLOSE);
               m_pMap->SetType(m_DoorStartX + 0, m_DoorStartY + 2, Block::BLOCK_DOOR_CLOSE);
               m_pMap->SetType(m_DoorStartX + 1, m_DoorStartY + 2, Block::BLOCK_DOOR_CLOSE);

               findDoorStartPos = true;

               break;
            }
         }

         if (g_stageNum == 3)
         {
            // 스테이지 03의 데이터에서 스프링를 찾아서 시작 위치를 찾음
            if (m_StageThreeData[y][x] == (int)Block::BLOCK_KEY)
            {
               m_KeyStartX = x;
               m_KeyStartY = y;

               break;
            }

            // 스테이지 03의 데이터에서 닫힌 문의 위치를 찾아서 세팅한다
            if (m_StageThreeData[y][x] == (int)Block::BLOCK_DOOR_CLOSE && findDoorStartPos == false)
            {
               findDoorStartPos = true;

               m_DoorStartX = x;
               m_DoorStartY = y;
               cout << "첫 도어 그리드 X = " << m_DoorStartX << " Y= " << m_DoorStartY << endl;

               break;
            }
         }
      }
   }

   /// 배열에 있는 값(원소) 중에 첫 -1을 찾아서 플레이어의 시작위치를 잡는 방법
   for (int y = 0; y < MAPSIZE_Y; y++)
   {
      for (int x = 0; x < MAPSIZE_X; x++)
      {
         if (m_pMap->GetType(x, y) == Block::CHAR_START_POS)
         {
            m_StartPosX = x * TILESIZE;
            m_StartPosY = (y * TILESIZE) - TILESIZE; // y좌표는 한칸 보전해줘야 한다.

            cout << y << "  " << x << "\n\n";

            break;
         }
      }
   }

   m_pPlayer->m_XDirection = 1;

   _gameState = Game_State::Edit;
   m_pPlayer->m_PosX = m_StartPosX;
   m_pPlayer->m_PosY = m_StartPosY - TILESIZE;

   // 다이 사운드 재생
   _sndDie->soundSeek(0);
   _sndDie->soundPlay();

   m_pPlayer->m_IsPlayerGotKey = FALSE;

   g_editModeCameraReset = false;

   // 카메라 좌표 설정
   m_CameraX = m_pPlayer->m_PosX - (WINSIZEX / 2);
   m_CameraY = m_pPlayer->m_PosY - (WINSIZEY / 2);
}

// 클리어시 화면 중지
void Scene05_Ingame::CheckStageClear()
{
   int PlayerGridX = (int)(m_pPlayer->m_PosX + TILESIZE / 2) / TILESIZE;				// 중심 좌표
   int PlayerGridY = (int)(m_pPlayer->m_PosY + TILESIZE + TILESIZE / 2) / TILESIZE;

   if (m_pMap->m_pGameBoard[PlayerGridY + 1][PlayerGridX]->m_Type == Block::BLOCK_FRUIT)
   {
      _gameState = Game_State::Stop;
   }
}

void Scene05_Ingame::SetClearLevel()
{
   if (_timer < _limitTime[0])
   {
      // 별 3개 
      g_clearLevel = 3;
   }

   else if (_timer < _limitTime[1])
   {
      // 별 2개
      g_clearLevel = 2;
   }

   else
   {
      // 별 1개
      g_clearLevel = 1;
   }

   // 디버그 콘솔 확인용
   cout << "제한 시간 : " << _limitTime[0] << "\n";
   cout << "제한 시간 : " << _limitTime[1] << "\n";
   cout << "클리어 타임 : " << _timer << "\n\n";
}

void Scene05_Ingame::SetLimitTime()
{
   /// 레벨 클리어 제한시간 조정
   switch (g_stageNum)
   {
      case 1:
         _limitTime[0] = 4.0f;
         _limitTime[1] = 8.0f;
         break;


      case 2:
         _limitTime[0] = 4.0f;
         _limitTime[1] = 7.5f;
         break;

      case 3:
         _limitTime[0] = 3.4f;
         _limitTime[1] = 5.0f;
         break;
   }
}

void Scene05_Ingame::DebugingKeyInput()
{
   /// 인게임 내 캐릭터 속성 조절
   if (KEYMANAGER->IsOnceKeyDown(VK_UP))
   {
      m_pPlayer->m_MaxJumpPower -= 1.0f;
   }

   if (KEYMANAGER->IsOnceKeyDown(VK_DOWN))
   {
      m_pPlayer->m_MaxJumpPower += 1.0f;
   }

   if (KEYMANAGER->IsOnceKeyDown(VK_LEFT))
   {
      m_pPlayer->m_Speed -= 1.0f;
   }

   if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT))
   {
      m_pPlayer->m_Speed += 1.0f;
   }

   if (KEYMANAGER->IsOnceKeyDown('T'))
   {
      m_pPlayer->m_SpringJumpPower -= 1.0f;
   }

   if (KEYMANAGER->IsOnceKeyDown('G'))
   {
      m_pPlayer->m_SpringJumpPower += 1.0f;
   }

   if (KEYMANAGER->IsOnceKeyDown(VK_CONTROL))
   {
      cout << "플레이어 방향전환 \n\n";
      m_pPlayer->ChangeDirection();
   }

   if (KEYMANAGER->IsOnceKeyDown('R'))
   {
      ResetStage();
   }

   if (KEYMANAGER->IsOnceKeyDown('Q'))
   {
      g_debugMode = !g_debugMode;
   }
}

void Scene05_Ingame::DebugDrawPlayerCollisionBox()
{
   // 타일 1칸의 크기를 1로 바꾼다
   int CurPosInTileX = ((int)(m_pPlayer->m_PosX + TILESIZE / 2) / TILESIZE) * TILESIZE;
   int CurPosInTileY = ((int)(m_pPlayer->m_PosY + TILESIZE / 2 + TILESIZE) / TILESIZE) * TILESIZE;

   DrawRectangleForDebug(g_backBuffer->GetMemDC(),		// 중심 좌표 노랑 박스
      m_pPlayer->m_PosX,
      m_pPlayer->m_PosY + TILESIZE,
      m_pPlayer->m_PosX + TILESIZE,
      m_pPlayer->m_PosY + TILESIZE * 2,
      RGB(255, 255, 0));

   DrawRectangleForDebug(g_backBuffer->GetMemDC(),		// 현재 소속 그리드 빨간 박스
      CurPosInTileX,				// left
      CurPosInTileY,				// top
      CurPosInTileX + TILESIZE,	// right 
      CurPosInTileY + TILESIZE,	// bottom
      RGB(255, 0, 0));

   DrawRectangleForDebug(g_backBuffer->GetMemDC(),		// 중심 좌표 빨강색 점
      m_pPlayer->m_PosX + TILESIZE / 2 - 1,
      m_pPlayer->m_PosY + TILESIZE + TILESIZE / 2 - 1,
      m_pPlayer->m_PosX + TILESIZE / 2 + 1,
      m_pPlayer->m_PosY + TILESIZE + TILESIZE / 2 + 1,
      RGB(255, 0, 255));
}

void Scene05_Ingame::DebugDrawPlayerCollisionBox()
{
   // 타일 1칸의 크기를 1로 바꾼다 -> 맵을 타일화 한다
   // int는 소수점을 버림한다는 스펙을 이용한다 
   int curPosAsTileX = ((int)(m_pPlayer->m_PosX + TILESIZE / 2) / TILESIZE) * TILESIZE;
   int curPosAsTileY = ((int)(m_pPlayer->m_PosY + TILESIZE / 2) / TILESIZE) * TILESIZE;

   // 중심 좌표 노랑 박스
   DrawRectangleForDebug(g_backBuffer->GetMemDC(),	// 더블버퍼링에 쓰일 memDC
      m_pPlayer->m_PosX,            // left
      m_pPlayer->m_PosY,            // top
      m_pPlayer->m_PosX + TILESIZE, // right 
      m_pPlayer->m_PosY + TILESIZE, // bottom
      RGB(255, 255, 0));            // color

   // 현재 소속 그리드 빨간 박스
   DrawRectangleForDebug(g_backBuffer->GetMemDC(),		
      curPosAsTileX,				   // left
      curPosAsTileY,				   // top
      curPosAsTileX + TILESIZE,	// right 
      curPosAsTileY + TILESIZE,	// bottom
      RGB(255, 0, 0));           // color

   // 중심 좌표 빨강색 점
   DrawRectangleForDebug(g_backBuffer->GetMemDC(),		
      m_pPlayer->m_PosX + TILESIZE / 2 - 1,  // left
      m_pPlayer->m_PosY + TILESIZE / 2 - 1,  // top
      m_pPlayer->m_PosX + TILESIZE / 2 + 1,  // right 
      m_pPlayer->m_PosY + TILESIZE / 2 + 1,  // bottom
      RGB(255, 0, 255));                     // color
}


void Scene05_Ingame::DebugShowInfo()
{
   int PosGridX = m_pPlayer->m_PosX + TILESIZE / 2;				// 중심 좌표
   int PosGridY = m_pPlayer->m_PosY + TILESIZE + TILESIZE / 2;

   TCHAR PosGridInfo[100];
   wsprintf(PosGridInfo, TEXT("현재 플레이어 위치 배열 X 좌표 = %d, 배열 Y 좌표 = %d"),
      (PosGridX / TILESIZE), (PosGridY / TILESIZE));
   TextOut(g_backBuffer->GetMemDC(), 10 + m_CameraX, 10 + m_CameraY, PosGridInfo, lstrlen(PosGridInfo));

   // 현재 마우스 좌표
   TCHAR mouseInfo[100];
   wsprintf(mouseInfo, TEXT("마우스 X 좌표 = %d, 마우스 Y 좌표 = %d"), m_ptMouse.x, m_ptMouse.y);
   TextOut(g_backBuffer->GetMemDC(), 10 + m_CameraX, 30 + m_CameraY, mouseInfo, lstrlen(mouseInfo));

   // 현재 마우스가 클릭한 배열 타입 값
   TCHAR mousePickedBlockInfo[100];
   wsprintf(mousePickedBlockInfo, TEXT("마우스 Picked Block_Type = %d"), m_PickedBlockType);
   TextOut(g_backBuffer->GetMemDC(), 10 + m_CameraX, 50 + m_CameraY, mousePickedBlockInfo, lstrlen(mousePickedBlockInfo));

   // 현재 캐릭터 정보
   // 이동속도
   TCHAR playerSpeed[100];
   wsprintf(playerSpeed, TEXT("캐릭터 Speed = %d"), m_pPlayer->m_Speed);
   TextOut(g_backBuffer->GetMemDC(), 10 + m_CameraX, 70 + m_CameraY, playerSpeed, lstrlen(playerSpeed));

   // 현재 점프파워
   TCHAR current_playerJumpPower[100];
   wsprintf(current_playerJumpPower, TEXT("캐릭터 JumpPower = %d"), static_cast<int>(m_pPlayer->m_JumpPower));
   TextOut(g_backBuffer->GetMemDC(), 10 + m_CameraX, 90 + m_CameraY, current_playerJumpPower, lstrlen(current_playerJumpPower));

   // 일반 점프파워
   TCHAR Max_playerJumpPower[150];
   wsprintf(Max_playerJumpPower, TEXT("캐릭터 JumpPower = %d"), static_cast<int>(m_pPlayer->m_MaxJumpPower));
   TextOut(g_backBuffer->GetMemDC(), 10 + m_CameraX, 110 + m_CameraY, Max_playerJumpPower, lstrlen(Max_playerJumpPower));

   // 스프링 점프파워
   TCHAR springJumpPower[150];
   wsprintf(springJumpPower, TEXT("캐릭터 스프링 JumpPower = %d"), static_cast<int>(m_pPlayer->m_SpringJumpPower));
   TextOut(g_backBuffer->GetMemDC(), 10 + m_CameraX, 130 + m_CameraY, springJumpPower, lstrlen(springJumpPower));

   //

   TextOut(g_backBuffer->GetMemDC(), 10 + m_CameraX, 150 + m_CameraY, L"일반   스피드 조절 [좌 우]", lstrlen(L"일반   스피드 조절 [좌 우]"));
   TextOut(g_backBuffer->GetMemDC(), 10 + m_CameraX, 170 + m_CameraY, L"일반   점프력 조절 [위 아래]", lstrlen(L"일반   점프력 조절 [위 아래]"));
   TextOut(g_backBuffer->GetMemDC(), 10 + m_CameraX, 190 + m_CameraY, L"스프링 점프력 조절 [T G]", lstrlen(L"스프링 점프력 조절 [T G]"));
   TextOut(g_backBuffer->GetMemDC(), 10 + m_CameraX, 210 + m_CameraY, L"방향 전환 [컨트롤Ctrl]", lstrlen(L"방향 전환 [컨트롤Ctrl]"));
   TextOut(g_backBuffer->GetMemDC(), 10 + m_CameraX, 230 + m_CameraY, L"스테이지 리셋 [R]", lstrlen(L"스테이지 리셋 [R]"));

   // 타이머 출력
   TCHAR time[150];
   wsprintf(time, TEXT("타이머 : %d"), static_cast<int>(_timer));
   TextOut(g_backBuffer->GetMemDC(), 10 + m_CameraX, 270 + m_CameraY, time, lstrlen(time));


   //cout << "캐릭터 JumpPower = " << _player->JumpPower << "\n\n";
}

void Scene05_Ingame::DebugShowMouseClickState()
{
   cout << "[마우스 왼클릭] \n";
   cout << "_ptMouse.x = " << m_ptMouse.x << "\n";
   cout << "_ptMouse.y = " << m_ptMouse.y << "\n";
   cout << "현재 선택 x칸 = " << m_ptMouse.x / TILESIZE << "\n";
   cout << "현재 선택 y칸 = " << m_ptMouse.y / TILESIZE << "\n\n";

   //
   cout << "m_CurPickedGameBoard = " << m_CurPickedGameBoard << "\n";
   cout << "PickedMouseBlockType = " << (int)m_PickedBlockType << "\n\n";

   // 보드 내용 디버깅용 출력
   cout << "[현재 m_FirstGameBoard] \n";
   for (int j = 0; j < MAPSIZE_Y; j++)
   {
      for (int i = 0; i < MAPSIZE_X; i++)
      {
         cout << (int)m_pMap->GetType(i, j) << " ";	/// 모르겠음...;;
      }
      cout << "\n\n";
   }
}

void Scene05_Ingame::CheckCurrentBoard(int x, int y)
{
   int CurMouseX = m_ptMouse.x / TILESIZE;
   int CurMouseY = m_ptMouse.y / TILESIZE;

   m_CurPickedGameBoard = m_pMap->GetBoardSet(CurMouseX, CurMouseY);
}

bool Scene05_Ingame::IsChangeMode()
{
   // SPACE 입력시 모드 전환
   if (KEYMANAGER->IsOnceKeyDown(VK_SPACE))
   {
      // 게임모드 전환하고
      if (_gameState == Game_State::Play)
      {
         cout << "Game Mode Change! [Play -> Edit]\n\n";
         _gameState = Game_State::Edit;
      }

      else if (_gameState == Game_State::Edit)
      {
         cout << "Game Mode Change! [Edit -> Play]\n\n";
         _gameState = Game_State::Play;
      }

      // 리턴 true
      return true;
   }

   // 게임모드가 바뀌지 않았음. 현재 모드 진행..
   return false;
}

void Scene05_Ingame::SelectButton()
{
   cout << "[SelectButtocn]\n";

   /// 버튼 클릭 사운드 재생(오류 있음)
   //_sndBtnClick->soundSeek(0);
   //_sndBtnClick->soundPlay();

   // 1칸 나무 버튼
   RECT btnWood = _imgWood->GetCollisionBox();

   // 3칸 나무 버튼
   RECT btnWood03 = _imgWoodL->GetCollisionBox();
   btnWood03.right += TILESIZE * 2;

   // 5칸 실제로 WoodL은 1칸 짜리므로 right를 4칸 더 보정한다.
   RECT btnWood05 = _imgWoodL->GetCollisionBox();
   btnWood05.right += TILESIZE * 4;

   // 스프링 버튼
   RECT btnSpring = _imgSpring->GetCollisionBox();

   // 키(열쇠) 버튼
   RECT btnKey = _imgKey->GetCollisionBox();

   // 닫힌 문 버튼
   RECT btnDoorClose = _imgDoorClose->GetCollisionBox();

   // 뒤로가기 버튼
   RECT btnGoBack = _imgGoBack->GetCollisionBox();

   // 리셋 버튼
   RECT btnReset = _imgReset->GetCollisionBox();

   if (PtInRect(&btnGoBack, m_ptMouse))
   {
      // 스테이지 씬으로
      // 뒤로 가기

      //g_editModeCameraReset = true;
      g_editModeCameraReset = false;

      SCENEMANAGER->ChangeScene("_stageScene");

      _sndBG->soundPause();

      return;
   }

   // 리셋 버튼
   if (PtInRect(&btnReset, m_ptMouse))
   {
      ResetStage();
   }


   // 선택 모드가 아닐 때 
   if (!m_IsSelectMode)
   {
      int x = static_cast<int>(m_ptMouse.x / TILESIZE);
      int y = static_cast<int>(m_ptMouse.y / TILESIZE);
      //Block typeOfCurBoard = m_pMap->GetType(x, y);

      /// 스테이지 번호에 따라 해당 스테이지의 초기 상태 보드에서 해당하는 지점의 타입이
      /// EMPTY 라면 그곳을 EMPTY로 만들어준다.(다시 빈 공간으로 만든다)
      switch (g_stageNum)
      {
         case 0:
            if (m_SampleData[y][x] == (int)Block::BLOCK_EMPTY)
            {
               m_pMap->SetType(x, y, Block::BLOCK_EMPTY);
               cout << "선택된 블록 파괴!\n\n";
            }
            break;

         case 1:
            if (m_StageOneData[y][x] == (int)Block::BLOCK_EMPTY)
            {
               m_pMap->SetType(x, y, Block::BLOCK_EMPTY);
               cout << "선택된 블록 파괴!\n\n";
            }
            break;

         case 2:
            if (m_StageTwoData[y][x] == (int)Block::BLOCK_EMPTY)
            {
               m_pMap->SetType(x, y, Block::BLOCK_EMPTY);
               cout << "선택된 블록 파괴!\n\n";
            }
            break;

         case 3:
            if (m_StageThreeData[y][x] == (int)Block::BLOCK_EMPTY)
            {
               m_pMap->SetType(x, y, Block::BLOCK_EMPTY);
               cout << "선택된 블록 파괴!\n\n";
            }
            break;
      }

      // 현재 선택중이 아닌데 버튼01을 클릭했나?
      if (PtInRect(&btnWood, m_ptMouse))
      {
         // 뭔가 타일을 선택중인 상태로 변경
         m_IsSelectMode = true;

         // 버튼01의 타입(WOOD) 저장
         m_PickedBlockType = Block::BLOCK_WOOD;

         cout << "버튼 01 클릭\n";
         cout << "현재 선택된 블록 = " << static_cast<int>(m_PickedBlockType) << "\n";
      }

      // 현재 선택중이 아닌데 버튼02을 클릭했나?
      if (PtInRect(&btnWood05, m_ptMouse))
      {
         // 뭔가 타일을 선택중인 상태로 변경
         m_IsSelectMode = true;

         // 버튼02의 타입 저장
         m_PickedBlockType = Block::BLOCK_WOOD_L;

         cout << "버튼 02 클릭\n";
         cout << "현재 선택된 블록 = " << static_cast<int>(m_PickedBlockType) << "\n";
      }

      // 현재 선택중이 아닌데 버튼03을 클릭했나?
      if (PtInRect(&btnSpring, m_ptMouse))
      {
         // 뭔가 타일을 선택중인 상태로 변경
         m_IsSelectMode = true;

         // 버튼03의 타입 저장
         m_PickedBlockType = Block::BLOCK_SPRING;

         cout << "버튼 03 클릭\n";
         cout << "현재 선택된 블록 = " << static_cast<int>(m_PickedBlockType) << "\n";
      }

      // 현재 선택중이 아닌데 버튼04을 클릭했나?
      if (PtInRect(&btnKey, m_ptMouse))
      {
         // 뭔가 타일을 선택중인 상태로 변경
         m_IsSelectMode = true;

         // 버튼04의 타입 저장
         m_PickedBlockType = Block::BLOCK_KEY;

         cout << "버튼 04 클릭\n";
         cout << "현재 선택된 블록 = " << static_cast<int>(m_PickedBlockType) << "\n";
      }

      // 3칸 나무 블록을 선택했나?
      if (PtInRect(&btnWood03, m_ptMouse))
      {
         // 뭔가 타일을 선택중인 상태로 변경
         m_IsSelectMode = true;

         // 버튼05의 타입 저장
         m_PickedBlockType = Block::BLOCK_WOOD_L;

         cout << "3칸 나무 버튼 클릭\n";
         cout << "현재 선택된 블록 = " << static_cast<int>(m_PickedBlockType) << "\n";
      }

      // 닫힌문 버튼 클릭
      if (PtInRect(&btnDoorClose, m_ptMouse))
      {
         // 뭔가 타일을 선택중인 상태로 변경
         m_IsSelectMode = true;

         // 버튼05의 타입 저장
         m_PickedBlockType = Block::BLOCK_DOOR_CLOSE;

         cout << "닫힌문 버튼 클릭\n";
         cout << "현재 선택된 블록 = " << static_cast<int>(m_PickedBlockType) << "\n";
      }

   }

   /// 선택중이었을 때 선택해제
   else
   {
      // 마우스의 좌표를 배열 요소로 샘플링 한다
      int CurMouseX = m_ptMouse.x / TILESIZE;
      int CurMouseY = m_ptMouse.y / TILESIZE;

      /// 게임 보드에서 현재 선택한 곳의 타입을 얻어온다.
      /// 아래 두 라인의 다른점 분석 필요
      Block temp = m_pMap->GetType(CurMouseX, CurMouseY);

      cout << "클릭한 곳의 블록 타입은 -> " << static_cast<int>(temp) << "\n\n";

      // 클릭한 곳이 비어있는 타일(EMPTY)이면
      if (temp == Block::BLOCK_EMPTY)
      {
         // 내가 집은 블록의 타입이 1칸짜리 블록이면
         if (m_PickedBlockType == Block::BLOCK_WOOD)
         {
            // 그 타일(칸)에 한칸짜리 블록을 넣는다.
            m_pMap->SetType(CurMouseX, CurMouseY, Block::BLOCK_WOOD);


            printf("배치 위치 = [%d,%d] / 배치 타입 = [%d]\n\n", CurMouseX, CurMouseY, Block::BLOCK_WOOD);

            // 다시 아무 것(블록)도 들고 있지 않는 상태로 변경
            m_PickedBlockType = Block::BLOCK_MOUSEEMPTY;
         }

         // 내가 집은 블록의 타입이 5칸짜리 블록이면
         if (m_PickedBlockType == Block::BLOCK_WOOD_L && (g_stageNum == 0 || g_stageNum == 1))
         {
            /// 선택한 칸부터 오른쪽으로 5칸의 타입을 알아와서 설치가능한지 판단한다
            for (int x = CurMouseX; x < CurMouseX + 5; x++)
            {
               if (m_pMap->GetType(x, CurMouseY) != Block::BLOCK_EMPTY)
               {
                  cout << "그 곳에는 설치 할 수 없다!\n\n";
                  return;
               }
            }

            /// 설치할 수 있다고 판단 되면
            // 각 나무 블록 설치(L, M, M, M, R)
            m_pMap->SetType(CurMouseX + 0, CurMouseY, Block::BLOCK_WOOD_L);
            m_pMap->SetType(CurMouseX + 1, CurMouseY, Block::BLOCK_WOOD_M);
            m_pMap->SetType(CurMouseX + 2, CurMouseY, Block::BLOCK_WOOD_M);
            m_pMap->SetType(CurMouseX + 3, CurMouseY, Block::BLOCK_WOOD_M);
            m_pMap->SetType(CurMouseX + 4, CurMouseY, Block::BLOCK_WOOD_R);

            printf("배치 위치 = [%d,%d] / 배치 타입 = [%d]\n\n", CurMouseX + 0, CurMouseY, Block::BLOCK_WOOD_L);
            printf("배치 위치 = [%d,%d] / 배치 타입 = [%d]\n\n", CurMouseX + 1, CurMouseY, Block::BLOCK_WOOD_M);
            printf("배치 위치 = [%d,%d] / 배치 타입 = [%d]\n\n", CurMouseX + 2, CurMouseY, Block::BLOCK_WOOD_M);
            printf("배치 위치 = [%d,%d] / 배치 타입 = [%d]\n\n", CurMouseX + 3, CurMouseY, Block::BLOCK_WOOD_M);
            printf("배치 위치 = [%d,%d] / 배치 타입 = [%d]\n\n", CurMouseX + 4, CurMouseY, Block::BLOCK_WOOD_R);

            // 다시 아무 것(블록)도 들고 있지 않는 상태로 변경
            m_PickedBlockType = Block::BLOCK_MOUSEEMPTY;
         }

         // 내가 집은 블록의 타입이 3칸짜리 블록이면
         // 스테이지 2, 3 은 3칸으로 처리
         if (m_PickedBlockType == Block::BLOCK_WOOD_L && (g_stageNum == 2 || g_stageNum == 3))
         {
            /// 선택한 칸부터 오른쪽으로 3칸의 타입을 알아와서 설치가능한지 판단한다
            for (int x = CurMouseX; x < CurMouseX + 3; x++)
            {
               if (m_pMap->GetType(x, CurMouseY) != Block::BLOCK_EMPTY)
               {
                  cout << "그 곳에는 설치 할 수 없다!\n\n";
                  return;
               }
            }

            /// 설치할 수 있다고 판단 되면
            // 각 나무 블록 설치(L, M, M, M, R)
            m_pMap->SetType(CurMouseX + 0, CurMouseY, Block::BLOCK_WOOD_L);
            m_pMap->SetType(CurMouseX + 1, CurMouseY, Block::BLOCK_WOOD_M);
            m_pMap->SetType(CurMouseX + 2, CurMouseY, Block::BLOCK_WOOD_R);

            printf("배치 위치 = [%d,%d] / 배치 타입 = [%d]\n\n", CurMouseX + 0, CurMouseY, Block::BLOCK_WOOD_L);
            printf("배치 위치 = [%d,%d] / 배치 타입 = [%d]\n\n", CurMouseX + 1, CurMouseY, Block::BLOCK_WOOD_M);
            printf("배치 위치 = [%d,%d] / 배치 타입 = [%d]\n\n", CurMouseX + 2, CurMouseY, Block::BLOCK_WOOD_R);

            // 다시 아무 것(블록)도 들고 있지 않는 상태로 변경
            m_PickedBlockType = Block::BLOCK_MOUSEEMPTY;
         }

         // 내가 집은 블록의 타입이 스프링 블록이면
         if (m_PickedBlockType == Block::BLOCK_SPRING)
         {
            // 선택한 블록은 비어 있고 
            // 1칸 아래에 뭔가 있으면서
            // 1칸 아래가 스프링이 아닐 떄
            if (m_pMap->GetType(CurMouseX, CurMouseY) == Block::BLOCK_EMPTY &&
               m_pMap->GetType(CurMouseX, CurMouseY + 1) != Block::BLOCK_EMPTY &&
               m_pMap->GetType(CurMouseX, CurMouseY + 1) != Block::BLOCK_SPRING)
            {
               // 그 타일(칸)에 스프링 블록을 넣는다.
               m_pMap->SetType(CurMouseX, CurMouseY, Block::BLOCK_SPRING);

               printf("배치 위치 = [%d,%d] / 배치 타입 = [%d]\n\n", CurMouseX, CurMouseY, Block::BLOCK_SPRING);

               // 다시 아무 것(블록)도 들고 있지 않는 상태로 변경
               m_PickedBlockType = Block::BLOCK_MOUSEEMPTY;
            }
            else
            {
               cout << "그 곳에는 설치 할 수 없다!\n\n";
               return;
            }
         }

         // 내가 집은 블록의 타입이 열쇠(키) 블록이면
         if (m_PickedBlockType == Block::BLOCK_KEY)
         {
            // 그 타일(칸)에 열쇠(키) 블록을 넣는다.
            m_pMap->SetType(CurMouseX, CurMouseY, Block::BLOCK_KEY);


            printf("배치 위치 = [%d,%d] / 배치 타입 = [%d]\n\n", CurMouseX, CurMouseY, Block::BLOCK_KEY);

            // 다시 아무 것(블록)도 들고 있지 않는 상태로 변경
            m_PickedBlockType = Block::BLOCK_MOUSEEMPTY;
         }

         // 내가 집은 블록의 타입이 닫힌 (문) 블록이면
         if (m_PickedBlockType == Block::BLOCK_DOOR_CLOSE)
         {
            for (int y = CurMouseY; y < CurMouseY + 3; y++)
            {
               for (int x = CurMouseX; x < CurMouseX + 2; x++)
               {
                  if (m_pMap->GetType(x, y) != Block::BLOCK_EMPTY)
                  {
                     cout << "그곳에는 문을 설치 할 수 없다\n\n";
                     return;
                  }
               }
            }

            // 기존의 문을 제거 하고
            for (int y = 0; y < MAPSIZE_Y; y++)
            {
               for (int x = 0; x < MAPSIZE_X; x++)
               {
                  if (m_pMap->GetType(x, y) == Block::BLOCK_DOOR_CLOSE)
                  {
                     m_pMap->SetType(x, y, Block::BLOCK_EMPTY);
                  }
               }
            }

            // 가로(2) * 세로(3) 칸에 닫힌 (문) 블록을 넣는다.
            m_pMap->SetType(CurMouseX + 0, CurMouseY + 0, Block::BLOCK_DOOR_CLOSE);
            m_pMap->SetType(CurMouseX + 1, CurMouseY + 0, Block::BLOCK_DOOR_CLOSE);
            m_pMap->SetType(CurMouseX + 0, CurMouseY + 1, Block::BLOCK_DOOR_CLOSE);
            m_pMap->SetType(CurMouseX + 1, CurMouseY + 1, Block::BLOCK_DOOR_CLOSE);
            m_pMap->SetType(CurMouseX + 0, CurMouseY + 2, Block::BLOCK_DOOR_CLOSE);
            m_pMap->SetType(CurMouseX + 1, CurMouseY + 2, Block::BLOCK_DOOR_CLOSE);

            printf("배치 위치 = [%d,%d] / 배치 타입 = [%d]\n\n", CurMouseX, CurMouseY, Block::BLOCK_KEY);

            // 다시 아무 것(블록)도 들고 있지 않는 상태로 변경
            m_PickedBlockType = Block::BLOCK_MOUSEEMPTY;
         }

         m_IsSelectMode = false;
         cout << "선택모드 해제~~~~\n\n";
      }

      /// 선택모드 중에 빈 칸이 아닌 곳을 클릭해서 설치가 불가능한 경우
      else
      {
         cout << "설치 불가(계속 선택모드) \n";
      }
   }
}

void Scene05_Ingame::RenderTile()
{
   bool isDrawDoor = false;	// false면 문을 그림 2 * 3 , true면 안 그림

   Block checkBlockType = Block::BLOCK_EMPTY;
   int renderPosX = 0;
   int renderPosY = 0;

   for (int y = 0; y < MAPSIZE_Y; y++)
   {
      for (int x = 0; x < MAPSIZE_X; x++)
      {
         checkBlockType = m_pMap->GetType(x, y);
         renderPosX = m_pMap->GetBox(x, y).left;
         renderPosY = m_pMap->GetBox(x, y).top;

         // 배치중이면 붉은 색상 이미지를 그림
         if (_gameState == Game_State::Edit)
         {
            switch (checkBlockType)
            {
               // 현재 타일이 비어있는 곳이면
               case Block::BLOCK_EMPTY:
               {
                  // 아무것도 안 그림
                  break;
               }
               case Block::BLOCK_KEY:
               {
                  _imgKey_R->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }
               case Block::BLOCK_DOOR_CLOSE:
               {
                  // 문을 그리지 않았을 때만 그림
                  if (!isDrawDoor)
                  {
                     _imgDoorClose_R->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);
                     isDrawDoor = true;
                  }
                  break;
               }
               case Block::BLOCK_DOOR_OPEN:
               {
                  // 문을 그리지 않았을 때만 그림
                  if (!isDrawDoor)
                  {
                     _imgDoorOpen_R->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);
                     isDrawDoor = true;
                  }
                  break;
               }

               case Block::BLOCK_SPRING:
               {
                  _imgSpring_R->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_FRUIT:
               {
                  _imgFruit->FrameRender(g_backBuffer->GetMemDC(), renderPosX - 70, renderPosY);

                  break;
               }

               case Block::BLOCK_WATER:
               {
                  _imgWater_R->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);
                  break;
               }

               case Block::BLOCK_UWATER:
               {
                  _imgUWater_R->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_UNDERGROUND02:
               {
                  _imgUnderGround02_R->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_UNDERGROUND03:
               {
                  _imgUnderGround03_R->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_WOOD:
               {
                  _imgWood_R->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_WOOD_L:
               {
                  _imgWoodL_R->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_WOOD_M:
               {
                  _imgWoodM_R->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_WOOD_R:
               {
                  _imgWoodR_R->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_GRASS_02:
               {
                  _imgGrass02_R->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_GRASS_03:
               {
                  _imgGrass03_R->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_GRASS_L:
               {
                  _imgGrassL_R->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_GRASS_L2:
               {
                  _imgGrassL2_R->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_GRASS_R:
               {
                  _imgGrassR_R->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_GRASS_R2:
               {
                  _imgGrassR2_R->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }
            }// end of Switch
         }

         // 배치중이 아니면 일반 색상 이미지를 그림
         else
         {
            switch (checkBlockType)
            {
               // 현재 타일이 비어있는 곳이면
               case Block::BLOCK_EMPTY:
               {
                  // 아무것도 안 그림
                  break;
               }

               case Block::BLOCK_UNDERGROUND02:
               {
                  _imgUnderGround02->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_UNDERGROUND03:
               {
                  _imgUnderGround03->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_KEY:
               {
                  _imgKey->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }
               case Block::BLOCK_DOOR_CLOSE:
               {
                  // 문을 그리지 않았을 때만 그림
                  if (!isDrawDoor)
                  {
                     _imgDoorClose->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);
                     isDrawDoor = true;
                  }
                  break;
               }
               case Block::BLOCK_DOOR_OPEN:
               {
                  // 문을 그리지 않았을 때만 그림
                  if (!isDrawDoor)
                  {
                     _imgDoorOpen->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);
                     isDrawDoor = true;
                  }
                  break;
               }

               case Block::BLOCK_SPRING:
               {
                  _imgSpring->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_WOOD:
               {
                  _imgWood->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_WOOD_L:
               {
                  _imgWoodL->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_WOOD_M:
               {
                  _imgWoodM->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_WOOD_R:
               {
                  _imgWoodR->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_FRUIT:
               {
                  _imgFruit->FrameRender(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_WATER:
               {
                  _imgWater->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);
                  break;
               }

               case Block::BLOCK_UWATER:
               {
                  _imgUWater->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_GRASS_02:
               {
                  _imgGrass02->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_GRASS_03:
               {
                  _imgGrass03->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_GRASS_L:
               {
                  _imgGrassL->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_GRASS_L2:
               {
                  _imgGrassL2->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_GRASS_R:
               {
                  _imgGrassR->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_GRASS_R2:
               {
                  _imgGrassR2->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_ROCK_01:
               {
                  _imgRock01->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_ROCK_02:
               {
                  _imgRock02->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_BUSH_01:
               {
                  _imgBush01->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }

               case Block::BLOCK_BUSH_02:
               {
                  _imgBush02->Render(g_backBuffer->GetMemDC(), renderPosX, renderPosY);

                  break;
               }
            }// end of Switch
         }
      }
   }
}

void Scene05_Ingame::RenderUI()
{
   // 공통 UI 렌더
   _imgBackBoard->Render(g_backBuffer->GetMemDC(), _imgBackBoard->GetX(), _imgBackBoard->GetY());
   _imgReset->Render(g_backBuffer->GetMemDC(), _imgReset->GetX(), _imgReset->GetY());
   _imgGoBack->Render(g_backBuffer->GetMemDC(), _imgGoBack->GetX(), _imgGoBack->GetY());

   // 스테이지 00(빈 맵) 버튼 렌더
   if (g_stageNum == 0)
   {
      _imgWood->Render(g_backBuffer->GetMemDC(), _imgWood->GetX(), _imgWood->GetY());

      _imgWoodL->Render(g_backBuffer->GetMemDC(), _imgWoodL->GetX(), _imgWoodL->GetY());
      _imgWoodM->Render(g_backBuffer->GetMemDC(), _imgWoodM->GetX(), _imgWoodM->GetY());
      _imgWoodM->Render(g_backBuffer->GetMemDC(), _imgWoodM->GetX() + 70, _imgWoodM->GetY());
      _imgWoodM->Render(g_backBuffer->GetMemDC(), _imgWoodM->GetX() + 140, _imgWoodM->GetY());
      _imgWoodR->Render(g_backBuffer->GetMemDC(), _imgWoodR->GetX(), _imgWoodL->GetY());

      _imgSpring->Render(g_backBuffer->GetMemDC(), _imgSpring->GetX(), _imgSpring->GetY());
      _imgKey->Render(g_backBuffer->GetMemDC(), _imgKey->GetX(), _imgKey->GetY());
      _imgDoorClose->Render(g_backBuffer->GetMemDC(), _imgDoorClose->GetX(), _imgDoorClose->GetY());
   }

   // 스테이지 01 버튼 렌더
   if (g_stageNum == 1)
   {
      _imgWood->Render(g_backBuffer->GetMemDC(), _imgWood->GetX(), _imgWood->GetY());

      _imgWoodL->Render(g_backBuffer->GetMemDC(), _imgWoodL->GetX(), _imgWoodL->GetY());
      _imgWoodM->Render(g_backBuffer->GetMemDC(), _imgWoodM->GetX(), _imgWoodM->GetY());
      _imgWoodM->Render(g_backBuffer->GetMemDC(), _imgWoodM->GetX() + 70, _imgWoodM->GetY());
      _imgWoodM->Render(g_backBuffer->GetMemDC(), _imgWoodM->GetX() + 140, _imgWoodM->GetY());
      _imgWoodR->Render(g_backBuffer->GetMemDC(), _imgWoodR->GetX(), _imgWoodR->GetY());
   }

   // 스테이지 02 버튼 렌더
   if (g_stageNum == 2)
   {
      _imgWood->Render(g_backBuffer->GetMemDC(), _imgWood->GetX(), _imgWood->GetY());

      _imgWoodL->Render(g_backBuffer->GetMemDC(), _imgWoodL->GetX(), _imgWoodL->GetY());
      _imgWoodM->Render(g_backBuffer->GetMemDC(), _imgWoodM->GetX(), _imgWoodM->GetY());
      _imgWoodR->Render(g_backBuffer->GetMemDC(), _imgWoodR->GetX(), _imgWoodR->GetY());
   }

   // 스테이지 03 버튼 렌더
   if (g_stageNum == 3)
   {
      _imgSpring->Render(g_backBuffer->GetMemDC(), _imgSpring->GetX(), _imgSpring->GetY());

      _imgWoodL->Render(g_backBuffer->GetMemDC(), _imgWoodL->GetX(), _imgWoodL->GetY());
      _imgWoodM->Render(g_backBuffer->GetMemDC(), _imgWoodM->GetX(), _imgWoodM->GetY());
      _imgWoodR->Render(g_backBuffer->GetMemDC(), _imgWoodR->GetX(), _imgWoodR->GetY());
   }
}

void Scene05_Ingame::ResetStage()
{
   cout << "스테이지 초기화!!\n\n";

   // 스테이지 초기화
   this->Init();

   //  카메라 위치 조정
   m_CameraX = m_pPlayer->m_PosX - (WINSIZEX / 2);
   m_CameraY = m_pPlayer->m_PosY - (WINSIZEY / 2);
}
