#include"DxLib.h"
#include"Resource.h"

int title[3];
int banner[3];
int yes;
int no;
int hand[3];
int win;
int lose;

typedef enum{
	 ModeLeady,
	 Mode,
	 TitleLeady,
	 Title,
	 TextLeady,
	 Text,
	 Q_oneLeady,
	 Q_one,
	 Q_twoLeady,
	 Q_two,
	 Q_threeLeady,
	 Q_three,
	 RSPLeady,
	 RSP,
	 ResaltLeady,
	 Resalt,
	 WinLeady,
	 Win,
	 LoseLeady,
	 Lose,
}eScene;

int Scene =  ModeLeady;

void Graph();
int StrongResalt( int j, int MasterHand, int victory);
int NomalResalt( int j, int MasterHand, int victory);
int WeakResalt( int j, int MasterHand, int victory);



int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR ipC, int nC){
	ChangeWindowMode(TRUE);
	DxLib_Init();
	SetDrawScreen( DX_SCREEN_BACK );

	DxLib::SetWindowTextA("����񂯂�Q�[��"); //�^�C�g�����Z�b�g
	SetWindowIconID(ID_ICON); //�A�C�R�����Z�b�g

	
	int x; //x���W
	int y; //y���W
	int White = GetColor(255,255,255); //��
	int i; //Q_two�p
	int j; //RSP�p
	int victory;
	int Mouse; //�}�E�X�ʒu
	int mode;
	int MasterHand = 0; //COM���̎�
	int cflag = 0; //�N���b�N�p�t���O
	int jflag = 0; //�����p�t���O

	Graph();

	while( !ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE) ){
	
		switch(Scene){

			case ModeLeady:{
				jflag = 0;
				victory = 0;
				mode = 0;
				
				Scene = Mode;
				break;
			}

			case Mode:{
				DrawFormatString( 10, 10, White, "���[�h��I�����Ă�������");
				DrawGraph( 10,  30, banner[0], TRUE);
				DrawGraph( 10, 180, banner[1], TRUE);
				DrawGraph( 10, 330, banner[2], TRUE);

				Mouse = GetMouseInput();
				GetMousePoint( &x, &y );
				/*-----Strong �I��-----*/
				if( 10 <= x && x < 630 && 30 <= y && y < 170){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						Scene = TitleLeady;
						mode = 0;
						cflag = 1;
					}
				}
				/*-----Nomal �I��-----*/
				if( 10 <= x && x < 630 && 180 <= y && y < 320){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						Scene = TitleLeady;
						mode = 1;
						cflag = 1;
					}
				}
				/*-----Weak �I��-----*/
				if( 10 <= x && x < 630 && 330 <= y && y < 470){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						Scene = TitleLeady;
						mode = 2;
						cflag = 1;
					}
				}
				if(( Mouse & MOUSE_INPUT_LEFT ) == 0){
					cflag = 0;
				}

				break;
			}

			case TitleLeady:{

				Scene = Title;
				break;
			}

			case Title:{
				DrawGraph( 0, 0, title[mode], TRUE);

				Mouse = GetMouseInput();
				GetMousePoint( &x, &y );
				if( 0 <= x && x < 640 && 0 <= y && y < 480){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						Scene = TextLeady;
						cflag = 1;
					}
				}
				if(( Mouse & MOUSE_INPUT_LEFT ) == 0){
					cflag = 0;
				}

				break;
			}

			case TextLeady:{

				/*-----Nomal �I���Ȃ�-----*/
				if( mode == 1 ){
					Scene = RSPLeady;
				}
				/*-----Strong � Weak �I���Ȃ�-----*/
				else{
					Scene = Text;
				}
				break;
			}

			case Text:{
				DrawFormatString( 110, 110, White, "�S������񂯂�̐��E�ւ悤�����B");
				DrawFormatString( 110, 150, White, "���ꂩ�炢������������܂��B");
				DrawFormatString( 110, 170, White, "�����̉񓚂���͂��Ă��Ȃ��̏o�����\�����܂��B");
				DrawFormatString( 110, 210, White, "���N���b�N�������Ď��̃y�[�W�Ɉړ����Ă��������B");

				Mouse = GetMouseInput();
				GetMousePoint( &x, &y );
				if( 0 <= x && x < 640 && 0 <= y && y < 480){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						Scene = Q_oneLeady;
						cflag = 1;
					}
				}
				if(( Mouse & MOUSE_INPUT_LEFT ) == 0){
					cflag = 0;
				}

				break;
			}

			case Q_oneLeady:{

				Scene = Q_one;
				break;
			}

			case Q_one:{
				DrawFormatString( 110, 50, White, "���Ȃ��͂ǂ̎���o�����Ƃ��Ă��܂���?");

				DrawGraph( 110, 300, hand[0], TRUE );
				DrawGraph( 260, 300, hand[1], TRUE );
				DrawGraph( 410, 300, hand[2], TRUE );

				Mouse = GetMouseInput();
				GetMousePoint( &x, &y );
				/*-----�O�[ �I��-----*/
				if( 110 <= x && x < 230 && 300 <= y && y < 420){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						Scene = Q_twoLeady;
						cflag = 1;
					}
				}
				/*-----�`���L �I��-----*/
				if( 260 <= x && x < 380 && 300 <= y && y < 420){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						Scene = Q_twoLeady;
						cflag = 1;
					}
				}
				/*-----�p�[ �I��-----*/
				if( 410 <= x && x < 530 && 300 <= y && y < 420){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						Scene = Q_twoLeady;
						cflag = 1;
					}
				}
				if(( Mouse & MOUSE_INPUT_LEFT ) == 0){
					cflag = 0;
				}

				break;
			}

			case Q_twoLeady:{
				i = GetRand(2);

				Scene = Q_two;
				break;
			}

			case Q_two:{
				switch(i){
				case 0:DrawFormatString( 110, 50, White, "�킽���̓O�[���o�����Ƃ��Ă��܂��B�M���Ă���܂���?"); break;
				case 1:DrawFormatString( 110, 50, White, "�킽���̓`���L���o�����Ƃ��Ă��܂��B�M���Ă���܂���?"); break;
				case 2:DrawFormatString( 110, 50, White, "�킽���̓p�[���o�����Ƃ��Ă��܂��B�M���Ă���܂���?"); break;
				}

				DrawGraph( 170, 300, yes, TRUE );
				DrawGraph( 350, 300, no, TRUE );

				Mouse = GetMouseInput();
				GetMousePoint( &x, &y );
				/*-----�͂� �I��-----*/
				if( 170 <= x && x < 290 && 300 <= y && y < 420){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						Scene = Q_threeLeady;
						cflag = 1;
					}
				}
				/*-----������ �I��-----*/
				if( 350 <= x && x < 470 && 300 <= y && y < 420){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						Scene = Q_threeLeady;
						cflag = 1;
					}
				}
				if(( Mouse & MOUSE_INPUT_LEFT ) == 0){
					cflag = 0;
				}

				break;
			}
			case Q_threeLeady:{

				Scene = Q_three;
				break;
			}

			case Q_three:{
				DrawFormatString( 110, 50,White,"���Ȃ��͂������I�񂾎���o�����Ǝv���Ă��܂����H");
				DrawFormatString( 110, 70,White,"(�R�����Ă����܂��܂���)");

				DrawGraph( 170, 300, yes, TRUE );
				DrawGraph( 350, 300, no, TRUE );

				Mouse = GetMouseInput();
				GetMousePoint( &x, &y );
				/*-----�͂� �I��-----*/
				if( 170 <= x && x < 290 && 300 <= y && y < 420){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						Scene = RSPLeady;
						cflag = 1;
					}
				}
				/*-----������ �I��-----*/
				if( 350 <= x && x < 470 && 300 <= y && y < 420){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						Scene = RSPLeady;
						cflag = 1;
					}
				}
				if(( Mouse & MOUSE_INPUT_LEFT ) == 0){
					cflag = 0;
				}

				break;
			}

			case RSPLeady:{

				Scene = RSP;
				break;
			}

			case RSP:{
				if( mode != 1 ){
					DrawFormatString( 110, 50,White,"�Ȃ�قǁA���Ȃ��̎肪�\�z�ł��܂����B");
				}
				if( victory == 2){
					DrawFormatString( 110, 70,White,"������x�����܂��B����񂯂�");
				}
				else{
					DrawFormatString( 110, 70,White,"�ł́A�����܂��B����񂯂�");
				}

				DrawGraph( 110, 300, hand[0], TRUE );
				DrawGraph( 260, 300, hand[1], TRUE );
				DrawGraph( 410, 300, hand[2], TRUE );

				Mouse = GetMouseInput();
				GetMousePoint( &x, &y );
				/*-----�O�[ �I��-----*/
				if( 110 <= x && x < 230 && 300 <= y && y < 420){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						MasterHand = 0;
						Scene = ResaltLeady;
						cflag = 1;
					}
				}
				/*-----�`���L �I��-----*/
				if( 260 <= x && x < 380 && 300 <= y && y < 420){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						MasterHand = 1;
						Scene = ResaltLeady;
						cflag = 1;
					}
				}
				/*-----�p�[ �I��-----*/
				if( 410 <= x && x < 530 && 300 <= y && y < 420){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						MasterHand = 2;
						Scene = ResaltLeady;
						cflag = 1;
					}
				}
				if(( Mouse & MOUSE_INPUT_LEFT ) == 0){
					cflag = 0;
				}

				break;
			}

			case ResaltLeady:{
				if( mode == 1){
					j = GetRand(2);
				}
				else{
					j = GetRand(9);
				}

				Scene = Resalt;
				break;
			}

			case Resalt:{
				DrawFormatString( 110, 50,White,"�ۂ�");

				switch(MasterHand){
					case 0: DrawGraph( 110, 300, hand[0], TRUE ); break;
					case 1: DrawGraph( 260, 300, hand[1], TRUE ); break;
					case 2: DrawGraph( 410, 300, hand[2], TRUE ); break;
				}

				switch(mode){
					case 0: victory = StrongResalt( j, MasterHand, victory); break;
					case 1: victory = NomalResalt( j, MasterHand, victory); break;
					case 2: victory = WeakResalt( j, MasterHand, victory); break;
				}

				Mouse = GetMouseInput();
				GetMousePoint( &x, &y );
				if( 0 <= x && x < 640 && 0 <= y && y < 480){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						switch(victory){
							case 0: Scene = WinLeady; break;
							case 1: Scene = LoseLeady; break;
							case 2: Scene = RSPLeady; break;
						}
						cflag = 1;
					}
				}
				if(( Mouse & MOUSE_INPUT_LEFT ) == 0){
					cflag = 0;
				}

				break;
			}

			case WinLeady:{

				Scene = Win;
				break;
			}

			case Win:{
				DrawGraph( 0, 0, win, TRUE );

				Mouse = GetMouseInput();
				GetMousePoint( &x, &y );
				if( 0 <= x && x < 640 && 0 <= y && y < 480){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						Scene = ModeLeady;
						cflag = 1;
					}
				}
				if(( Mouse & MOUSE_INPUT_LEFT ) == 0){
					cflag = 0;
				}

				break;
			}

			case LoseLeady:{

				Scene = Lose;
				break;
			}

			case Lose:{
				DrawGraph( 0, 0, lose, TRUE );

				Mouse = GetMouseInput();
				GetMousePoint( &x, &y );
				if( 0 <= x && x < 640 && 0 <= y && y < 480){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						Scene = ModeLeady;
						cflag = 1;
					}
				}
				if(( Mouse & MOUSE_INPUT_LEFT ) == 0){
					cflag = 0;
				}

				break;
			}

		}

	}

	DxLib_End();
	return 0;
}



void Graph(){

	title[0] = LoadGraph("����񂯂�/strong.png");
	title[1] = LoadGraph("����񂯂�/nomal.png");
	title[2] = LoadGraph("����񂯂�/weak.png");

	banner[0] = LoadGraph("����񂯂�/SBanner.png");
	banner[1] = LoadGraph("����񂯂�/NBanner.png");
	banner[2] = LoadGraph("����񂯂�/WBanner.png");

	yes = LoadGraph("����񂯂�/�͂�.png");
	no = LoadGraph("����񂯂�/������.png");

	hand[0] = LoadGraph("����񂯂�/gu-.png");
	hand[1] = LoadGraph("����񂯂�/choki.png");
	hand[2] = LoadGraph("����񂯂�/pa-.png");

	win = LoadGraph( "����񂯂�/YouWin.png" );
	lose = LoadGraph( "����񂯂�/YouLose.png" );

}


int StrongResalt( int j, int MasterHand, int victory){

	/*-----���Ԃ�̂���-----*/
	if(j == 7){
		switch(MasterHand){
			case 0:{
				DrawGraph( 260, 100, hand[1], TRUE );
				victory = 0;
				break;
			}
			case 1:{
				DrawGraph( 260, 100, hand[2], TRUE );
				victory = 0;
				break;
			}
			case 2:{
				DrawGraph( 260, 100, hand[0], TRUE );
				victory = 0;
				break;
			}
		}
	}
	/*-----���Ԃ�̂܂�-----*/
	else{
		switch(MasterHand){

			case 0:{
				DrawGraph( 260, 100, hand[2], TRUE );
				victory = 1;
				break;
			}
			case 1:{
				DrawGraph( 260, 100, hand[0], TRUE );
				victory = 1;
				break;
			}
			case 2:{
				DrawGraph( 260, 100, hand[1], TRUE );
				victory = 1;
				break;
			}
		}
	}

	return(victory);
}

int NomalResalt( int j, int MasterHand, int victory){

	/*-----���Ԃ�̂���-----*/
	if(j == 0){
		switch(MasterHand){
			case 0:{
				DrawGraph( 260, 100, hand[1], TRUE );
				victory = 0;
				break;
			}
			case 1:{
				DrawGraph( 260, 100, hand[2], TRUE );
				victory = 0;
				break;
			}
			case 2:{
				DrawGraph( 260, 100, hand[0], TRUE );
				victory = 0;
				break;
			}
		}
	}
	/*-----���Ԃ�̂܂�-----*/
	if(j == 1){
		switch(MasterHand){
			case 0:{
				DrawGraph( 260, 100, hand[2], TRUE );
				victory = 1;
				break;
			}
			case 1:{
				DrawGraph( 260, 100, hand[0], TRUE );
				victory = 1;
				break;
			}
			case 2:{
				DrawGraph( 260, 100, hand[1], TRUE );
				victory = 1;
				break;
			}
		}
	}
	/*-----������-----*/
	if(j == 2){
		switch(MasterHand){
			case 0:{
				DrawGraph( 260, 100, hand[0], TRUE );
				victory = 2;
				break;
			}
			case 1:{
				DrawGraph( 260, 100, hand[1], TRUE );
				victory = 2;
				break;
			}
			case 2:{
				DrawGraph( 260, 100, hand[2], TRUE );
				victory = 2;
				break;
			}
		}
	}

	return(victory);
}

int WeakResalt( int j, int MasterHand, int victory){

	/*-----���Ԃ�̂܂�-----*/
	if(j == 4){
		switch(MasterHand){
			case 0:{
				DrawGraph( 260, 100, hand[2], TRUE );
				victory = 1;
				break;
			}
			case 1:{
				DrawGraph( 260, 100, hand[0], TRUE );
				victory = 1;
				break;
			}
			case 2:{
				DrawGraph( 260, 100, hand[1], TRUE );
				victory = 1;
				break;
			}
		}
	}
	/*-----���Ԃ�̂���-----*/
	else{
		switch(MasterHand){
			case 0:{
				DrawGraph( 260, 100, hand[1], TRUE );
				victory = 0;
				break;
			}
			case 1:{
				DrawGraph( 260, 100, hand[2], TRUE );
				victory = 0;
				break;
			}
			case 2:{
				DrawGraph( 260, 100, hand[0], TRUE );
				victory = 0;
				break;
			}
		}
	}

	return(victory);
}
