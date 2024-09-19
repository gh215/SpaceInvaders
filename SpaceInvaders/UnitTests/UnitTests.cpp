#include "pch.h"
#include "CppUnitTest.h"
#include "..\SpaceInvaders\SpaceInvaders_header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		
		TEST_METHOD(TestIsOnFire)
		{
			int x0 = FIELD_WIDTH / 2;
			int y0 = FIELD_HEIGHT / 2;
			/*			
							### ###
							 $   $
						    ###
							 $		
			*/
			vector<Alien> aliens;
			Alien cannotShoot(x0, y0);
			Alien canShoot1(x0 + ALIEN_H_INTERVAL, y0);
			Alien canShoot2(x0, y0 + ALIEN_V_INTERVAL);
			
			aliens.push_back(cannotShoot);
			aliens.push_back(canShoot1);
			aliens.push_back(canShoot2);

			Assert::IsTrue(cannotShoot.isOnFire(aliens));
			Assert::IsFalse(canShoot1.isOnFire(aliens));
			Assert::IsFalse(canShoot2.isOnFire(aliens));
			


		}
	};
}
