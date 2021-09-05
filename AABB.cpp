#include "pch.h"
#include "AABB.h"
#include "Player.h"

// 2개의 축정렬충돌 사각형을 받아서 충돌 감지 체크
bool CheckCollision_AABB(RECT source, RECT target)
{
   if (source.left <= target.right && target.left <= source.right &&
       source.top <= target.bottom && target.top <= source.bottom)
   {
      return true;
   }

   return false;
}

bool CheckCollision_AABB_X(RECT source, RECT target)
{
   if (source.left <= target.right && target.left <= source.right)
   {
      return true;
   }

   return false;
}

bool CheckCollision_AABB_Y(RECT source, RECT target)
{
   if (source.top <= target.bottom && target.top <= source.bottom)
   {
      return true;
   }

   return false;
}

// 
bool Check_Same_Y_axis(RECT source, RECT target)
{
   if (source.left == target.left &&
      source.right == target.right)
   {
      return true;
   }

   return false;
}