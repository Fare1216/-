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

	DxLib::SetWindowTextA("じゃんけんゲーム"); //タイトルをセット
	SetWindowIconID(ID_ICON); //アイコンをセット

	
	int x; //x座標
	int y; //y座標
	int White = GetColor(255,255,255); //白
	int i; //Q_two用
	int j; //RSP用
	int victory;
	int Mouse; //マウス位置
	int mode;
	int MasterHand = 0; //COM側の手
	int cflag = 0; //クリック用フラグ
	int jflag = 0; //乱数用フラグ

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
				DrawFormatString( 10, 10, White, "モードを選択してください");
				DrawGraph( 10,  30, banner[0], TRUE);
				DrawGraph( 10, 180, banner[1], TRUE);
				DrawGraph( 10, 330, banner[2], TRUE);

				Mouse = GetMouseInput();
				GetMousePoint( &x, &y );
				/*-----Strong 選択-----*/
				if( 10 <= x && x < 630 && 30 <= y && y < 170){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						Scene = TitleLeady;
						mode = 0;
						cflag = 1;
					}
				}
				/*-----Nomal 選択-----*/
				if( 10 <= x && x < 630 && 180 <= y && y < 320){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						Scene = TitleLeady;
						mode = 1;
						cflag = 1;
					}
				}
				/*-----Weak 選択-----*/
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

				/*-----Nomal 選択なら-----*/
				if( mode == 1 ){
					Scene = RSPLeady;
				}
				/*-----Strong ･ Weak 選択なら-----*/
				else{
					Scene = Text;
				}
				break;
			}

			case Text:{
				DrawFormatString( 110, 110, White, "心理じゃんけんの世界へようこそ。");
				DrawFormatString( 110, 150, White, "これからいくつか質問をします。");
				DrawFormatString( 110, 170, White, "それらの回答を解析してあなたの出す手を予測します。");
				DrawFormatString( 110, 210, White, "左クリックを押して次のページに移動してください。");

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
				DrawFormatString( 110, 50, White, "あなたはどの手を出そうとしていますか?");

				DrawGraph( 110, 300, hand[0], TRUE );
				DrawGraph( 260, 300, hand[1], TRUE );
				DrawGraph( 410, 300, hand[2], TRUE );

				Mouse = GetMouseInput();
				GetMousePoint( &x, &y );
				/*-----グー 選択-----*/
				if( 110 <= x && x < 230 && 300 <= y && y < 420){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						Scene = Q_twoLeady;
						cflag = 1;
					}
				}
				/*-----チョキ 選択-----*/
				if( 260 <= x && x < 380 && 300 <= y && y < 420){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						Scene = Q_twoLeady;
						cflag = 1;
					}
				}
				/*-----パー 選択-----*/
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
				case 0:DrawFormatString( 110, 50, White, "わたしはグーを出そうとしています。信じてくれますか?"); break;
				case 1:DrawFormatString( 110, 50, White, "わたしはチョキを出そうとしています。信じてくれますか?"); break;
				case 2:DrawFormatString( 110, 50, White, "わたしはパーを出そうとしています。信じてくれますか?"); break;
				}

				DrawGraph( 170, 300, yes, TRUE );
				DrawGraph( 350, 300, no, TRUE );

				Mouse = GetMouseInput();
				GetMousePoint( &x, &y );
				/*-----はい 選択-----*/
				if( 170 <= x && x < 290 && 300 <= y && y < 420){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						Scene = Q_threeLeady;
						cflag = 1;
					}
				}
				/*-----いいえ 選択-----*/
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
				DrawFormatString( 110, 50,White,"あなたはさっき選んだ手を出そうと思っていますか？");
				DrawFormatString( 110, 70,White,"(嘘をついてもかまいません)");

				DrawGraph( 170, 300, yes, TRUE );
				DrawGraph( 350, 300, no, TRUE );

				Mouse = GetMouseInput();
				GetMousePoint( &x, &y );
				/*-----はい 選択-----*/
				if( 170 <= x && x < 290 && 300 <= y && y < 420){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						Scene = RSPLeady;
						cflag = 1;
					}
				}
				/*-----いいえ 選択-----*/
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
					DrawFormatString( 110, 50,White,"なるほど、あなたの手が予想できました。");
				}
				if( victory == 2){
					DrawFormatString( 110, 70,White,"もう一度いきます。じゃんけん");
				}
				else{
					DrawFormatString( 110, 70,White,"では、いきます。じゃんけん");
				}

				DrawGraph( 110, 300, hand[0], TRUE );
				DrawGraph( 260, 300, hand[1], TRUE );
				DrawGraph( 410, 300, hand[2], TRUE );

				Mouse = GetMouseInput();
				GetMousePoint( &x, &y );
				/*-----グー 選択-----*/
				if( 110 <= x && x < 230 && 300 <= y && y < 420){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						MasterHand = 0;
						Scene = ResaltLeady;
						cflag = 1;
					}
				}
				/*-----チョキ 選択-----*/
				if( 260 <= x && x < 380 && 300 <= y && y < 420){
					if( Mouse & MOUSE_INPUT_LEFT && cflag == 0){
						MasterHand = 1;
						Scene = ResaltLeady;
						cflag = 1;
					}
				}
				/*-----パー 選択-----*/
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
				DrawFormatString( 110, 50,White,"ぽん");

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

	title[0] = LoadGraph("じゃんけん/strong.png");
	title[1] = LoadGraph("じゃんけん/nomal.png");
	title[2] = LoadGraph("じゃんけん/weak.png");

	banner[0] = LoadGraph("じゃんけん/SBanner.png");
	banner[1] = LoadGraph("じゃんけん/NBanner.png");
	banner[2] = LoadGraph("じゃんけん/WBanner.png");

	yes = LoadGraph("じゃんけん/はい.png");
	no = LoadGraph("じゃんけん/いいえ.png");

	hand[0] = LoadGraph("じゃんけん/gu-.png");
	hand[1] = LoadGraph("じゃんけん/choki.png");
	hand[2] = LoadGraph("じゃんけん/pa-.png");

	win = LoadGraph( "じゃんけん/YouWin.png" );
	lose = LoadGraph( "じゃんけん/YouLose.png" );

}


int StrongResalt( int j, int MasterHand, int victory){

	/*-----じぶんのかち-----*/
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
	/*-----じぶんのまけ-----*/
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

	/*-----じぶんのかち-----*/
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
	/*-----じぶんのまけ-----*/
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
	/*-----あいこ-----*/
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

	/*-----じぶんのまけ-----*/
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
	/*-----じぶんのかち-----*/
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
