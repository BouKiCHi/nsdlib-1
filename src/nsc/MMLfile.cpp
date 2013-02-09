#include "StdAfx.h"
#include "MMLfile.h"

//==============================================================
//		コンストラクタ
//--------------------------------------------------------------
//	●引数
//		const	char*	strFileName		ファイル名
//	●返値
//				無し
//==============================================================
MMLfile::MMLfile(const char*	strFileName):
	offset_Ei(0),
	offset_Ev(0),
	offset_En(0),
	offset_Em(0),
	timebase(24),
	octave_reverse(false),
//	f_macro(false),
	p_macro(0),
	f_macro2(false)
	{
	//File open
	nowFile	= new FileInput();

	nowFile->fileopen(strFileName);
	ptcFiles.push_back(nowFile);

	iFiles = 0;
}

//==============================================================
//		デストラクタ
//--------------------------------------------------------------
//	●引数
//				無し
//	●返値
//				無し
//==============================================================
MMLfile::~MMLfile(void)
{

	//----------------------
	//Local変数
	vector	<FileInput*>::iterator	itFiles;

	//----------------------
	//Delete Class
	itFiles = ptcFiles.begin();
	while(itFiles != ptcFiles.end()){
		(*itFiles)->close();
		delete *itFiles;
		itFiles++;
	}
	ptcFiles.clear();

}

//==============================================================
//			現在コンパイル処理中のファイルの[EOF]チェック
//--------------------------------------------------------------
//	●引数
//			無し
//	●返値
//			bool		true	[EOF]を検出
//						false	まだ終わりじゃない。
//==============================================================
bool	MMLfile::eof(void)
{
	return( nowFile->eof() );
}

//==============================================================
//			MMLファイルの終了チェック
//--------------------------------------------------------------
//	●引数
//			無し
//	●返値
//			bool		true	元ファイルで[EOF]を検出
//						false	まだ終わりじゃない。
//==============================================================
bool	MMLfile::eom(void)
{
	if(( iFiles == 0 ) && ( eof() )){
		return(true);
	}
	return(false);
}

//==============================================================
//		インクルードファイル
//--------------------------------------------------------------
//	●引数
//			無し
//	●返値
//			無し
//	●処理
//			現在のファイルポインタに書いてあるファイルをインクルードする
//==============================================================
void	MMLfile::include()
{
	//----------------------
	//Local変数
	vector	<FileInput*>::iterator	itFiles;
	string	_name = GetString();

	//----------------------
	//同じファイルが開かれていないかチェック
	itFiles = ptcFiles.begin();
	while(itFiles != ptcFiles.end()){
		if( *(*itFiles)->GetFilename() == _name ){
			Err(L"既に同じファイルが#includeで開かれています。");
		}
		itFiles++;
	}

	//----------------------
	//File open
	nowFile	= new FileInput();

	nowFile->fileopen(_name.c_str());
	ptcFiles.push_back(nowFile);

	iFiles++; 
}

//==============================================================
//		マクロの設定
//--------------------------------------------------------------
//	●引数
//				無し
//	●返値
//				無し
//	●処理
//			現在のファイルポインタに書いてあるマクロを定義する。
//==============================================================
void	MMLfile::SetMacro(void)
{
	char	cData;
	string	macro_name		="";
	string	macro_contents	="";

	//------------------
	//マクロ名の取得
	while((cData = cRead()) > 0x20){
		if(cData == '{'){
			break;
		}
		macro_name += cData;
	};
	Back();

	//------------------
	//マクロ名の重複チェック
	if(ptcMac.count(macro_name) != 0){
		Err(L"既にそのマクロ名は存在しています。");
	}

	//------------------
	//マクロ内容の取得
	while(cRead() != '{'){
		if(eof()){
			Err(L"文字列開始を示す{が見つかりません。");
		}
	}

	while('}' != (cData = cRead())){
		if(eof()){
			Err(L"文字列終了を示す}が見つかりません。");
		}
		macro_contents += cData;
	}
	macro_contents += " ";

	//------------------
	//マクロ内容の設定
	ptcMac[macro_name] = macro_contents;
}

//==============================================================
//		マクロの呼び出し
//--------------------------------------------------------------
//	●引数
//				無し
//	●返値
//				無し
//	●処理
//			現在のファイルポインタに書いてあるマクロを呼び出す
//==============================================================
void	MMLfile::CallMacro(void)
{
	char		cData;
	int			i		= 0;
	string		_name	= "";

	//------------------
	//マクロ名の取得
	while((cData = cRead()) > 0x20){
		_name += cData;
	};
	Back();

	//------------------
	//マクロ名の存在チェック
	if(ptcMac.count(_name) == 0){
		Err(L"そのマクロ名は存在していません。");
	}

	//------------------
	//マクロ名の重複チェック
	while(i < p_macro){
		if(s_macro[i].name == _name){
			Err(L"マクロ内で同じマクロを呼び出しています。");
		}
		i++;
	}

	//------------------
	//ネストだったら保存
	if(p_macro > 0){
		s_macro[p_macro-1].name = nowMacro.name;
		s_macro[p_macro-1].line = nowMacro.line;
	}

	nowMacro.name = _name;
	nowMacro.line = 0;

	s_macro.push_back(nowMacro);
	p_macro++;

}

//==============================================================
//			現在コンパイル処理中のファイルポインタの取得
//--------------------------------------------------------------
//	●引数
//			無し
//	●返値
//			int		現在のファイルポインタ
//==============================================================
int		MMLfile::tellg(void)
{
	int	i;

	if(p_macro > 0){
		i = nowMacro.line;
	} else {
		i = nowFile->tellg();
	}

	return(i);
}

//==============================================================
//			現在コンパイル処理中のファイルポインタを絶対的に移動
//--------------------------------------------------------------
//	●引数
//			long	iSize	移動値
//	●返値
//			無し
//==============================================================
void	MMLfile::StreamPointerMove(long iSize)
{
	if(p_macro > 0){
		nowMacro.line = iSize;
	} else {
		nowFile->StreamPointerMove(iSize);
	}
}

//==============================================================
//			現在コンパイル処理中のファイルポインタを一つ戻す
//--------------------------------------------------------------
//	●引数
//			無し
//	●返値
//			無し
//==============================================================
void	MMLfile::Back(void)
{

	if(f_macro2 == true){
		f_macro2 = false;
		if(p_macro > 0){
			s_macro[p_macro-1].name = nowMacro.name;
			s_macro[p_macro-1].line = nowMacro.line;
		}
		p_macro++;
		nowMacro.name = s_macro[p_macro-1].name;
		nowMacro.line = s_macro[p_macro-1].line;
		nowMacro.line--;
	} else {
		if(p_macro > 0){
			nowMacro.line--;
		} else {
			nowFile->Back();
		}
	}

}

//==============================================================
//			１Byte読み込み
//--------------------------------------------------------------
//	●引数
//			無し
//	●返値
//			char	読み込み値
//==============================================================
char	MMLfile::cRead(void)
{
	char	cData;

	if(f_macro2 == true){
		f_macro2	= false;
		s_macro.pop_back();
	}
	if(p_macro > 0){
		cData = ptcMac[nowMacro.name][nowMacro.line];
		nowMacro.line++;
		if(ptcMac[nowMacro.name].size() == nowMacro.line){
			s_macro[p_macro-1].name = nowMacro.name;
			s_macro[p_macro-1].line = nowMacro.line;
			p_macro--;
			f_macro2	= true;
			if(p_macro > 0){
				nowMacro.name = s_macro[p_macro-1].name;
				nowMacro.line = s_macro[p_macro-1].line;
			}
		}
	} else {
		cData		= nowFile->cRead();
	}

	return(cData);
}

//==============================================================
//			１Byte読み込み（チェック付き）
//--------------------------------------------------------------
//	●引数
//			無し
//	●返値
//			char	読み込み値
//	●処理
//		１文字の読み込み。
//		但し、以下の記述があった場合は、そこを飛ばす。
//			・0x20以下のキャラクターコード
//			・コメント
//		また、インクルードファイル中で[EOF]を検出したら、前のファイルに戻る
//==============================================================
char	MMLfile::GetChar(void)		//1Byteの読み込み
{
	unsigned	char	cData;

	do{
		cData = cRead();

		//[EOM]？
		if( eom() )
		{
			return(0);

		//[EOF]？
		} else if( eof() ){
			nowFile->close();
			delete	nowFile;
			ptcFiles.pop_back();
			nowFile = ptcFiles.back();
			iFiles--;
			//continue

		//0x20以下の制御コード
		} else if(cData <= 0x20){
			//continue

		//アセンブリ言語タイプのコメント？
		} else if(cData == ';'){
			do{
				cData = cRead();		//次のバイトを読み込み
			} while((cData != 0x0A)||eof());
		
		//Ｃ言語タイプのコメント？
		} else 	if(cData == '/'){
			cData = cRead();		//次のバイトを読み込み
			switch(cData){

				//１行コメント
				case('/'):
					do{
						cData = cRead();		//次のバイトを読み込み
					}while((cData != 0x0A)||eof());
					break;

				//範囲コメント
				case('*'):
					do{
						do{
							cData = cRead();		//次のバイトを読み込み
							if(eof()){
								Err(L"コメント終端 */ がありません。");
							}
						}while(cData != '*');
						cData = cRead();
						Back();					//StreamPointerAdd(-1);
					} while(cData != '/');
							cRead();			//StreamPointerAdd(+1); をしたい。
					break;

				//それ以外
				default:
					Err(L"コメントですか？");
					break;
			}

		//[EOF]でも、コメントでも無い場合。
		} else {
			break;		//while(1) の break;
		}

	}while(1);

	return(cData);
}

//==============================================================
//			文字列読み込み
//--------------------------------------------------------------
//	●引数
//			無し
//	●返値
//			string	読み込んだ文字列
//	●処理
//			MML中で"と"で囲まれた文字列を取得する。
//==============================================================
string	MMLfile::GetString(void)
{
	char	cData;
	
	string	_str;
	while(cRead() != '"'){
		if(eof()){
			Err(L"文字列開始を示す\"が見つかりません。");
		}
	}

	while('"' != (cData = cRead())){
		if(eof()){
			Err(L"文字列終了を示す\"が見つかりません。");
		}
		_str += cData;
	}
	return(_str);
}

//==============================================================
//			数値読み込み
//--------------------------------------------------------------
//	●引数
//			無し
//	●返値
//			int		読み込んだ数値
//	●処理
//			MML中で(と)で囲まれた文字列を取得する。
//==============================================================
int	MMLfile::GetNum(void)
{
	char	cData;
	int		iResult;

	while(cRead() != '('){
		if(eof()){
			Err(L"数値開始を示す(が見つかりません。");
		}
	}

	iResult = GetInt();

	while(')' != (cData = cRead())){
		if(eof()){
			Err(L"数値終了を示す)が見つかりません。");
		}
	}
	return(iResult);
}

//==============================================================
//			数値読み込み
//--------------------------------------------------------------
//	●引数
//			無し
//	●返値
//			int		読み込んだ数値
//==============================================================
int		MMLfile::GetInt(void)
{
				bool	neg = false;			//符号
				int		iResult = 0;			//演算結果
	unsigned	char	cData = GetChar();

	//16進数
	if(cData == '$'){
		cData = cRead();
		if(cData == '+'){
			neg = false;
			cData	 = cRead();
		}
		if(cData == '-'){
			neg = true;
			cData	 = cRead();
		}
		while(((cData >= '0') && (cData <= '9')) || ((cData >= 'a') && (cData <= 'f')) || ((cData >= 'A') && (cData <= 'F'))){
			iResult <<= 4;
			if((cData >= '0') && (cData <= '9')){
				iResult += (unsigned int)cData - 0x30;
			} else if((cData >= 'A') && (cData <= 'F')){
				iResult += (unsigned int)cData - 0x41 + 10;
			} else if((cData >= 'a') && (cData <= 'f')){
				iResult += (unsigned int)cData - 0x61 + 10;
			}
			cData	 = cRead();
		}

	//２進数
	} else if(cData == '%'){
		cData = cRead();
		if(cData == '-'){
			neg = true;
			cData	 = cRead();
		}
		while((cData >= '0') && (cData <= '1')){
			iResult <<= 1;
			iResult += (unsigned int)cData - 0x30;
			cData	 = cRead();
		}

	//10進数
	} else if(((cData >= '0') && (cData <= '9')) || (cData == '-') || (cData == '+')){
		if(cData == '+'){
			neg = false;
			cData	 = cRead();
		}
		if(cData == '-'){
			neg = true;
			cData	 = cRead();
		}
		while((cData >= '0') && (cData <= '9')){
			iResult *= 10;
			iResult += (unsigned int)cData - 0x30;
			cData	 = cRead();
		}

	} else {
			Err(L"数値以外が指定されました。");
	}

	//ポインタを１つ戻す
	Back();							//	StreamPointerAdd(-1);

	//符号
	if(neg == true){
		iResult = -iResult;
	}

	return(iResult);
}

//==============================================================
//			音長読み込み
//--------------------------------------------------------------
//	●引数
//			int		記載がない場合の音長[tick]
//	●返値
//			int		音長[tick]
//	●処理
//		音長を読み込む（付点付き）
//==============================================================
int	MMLfile::readLength(unsigned int DefaultLength){

	char	cData;				//読み込み用
	int		iLength;			//音長 [tick]
	int		iDot;				//付点計算用 [tick]
	int		iMod;
	int		i;

	//読み込み
	cData = GetChar();

	//Length
	if(((cData >= '0') && (cData <= '9')) || (cData == '.')){
		//ポインタを１つ戻す
		Back();							//StreamPointerAdd(-1);
		if((cData >= '0') && (cData <= '9')){
			i = GetInt();
			iLength = (timebase * 4) / i;
			iMod	= (timebase * 4) % i;
			if(iMod != 0){
				Warning(L"音長の計算で割り切れませんでした。小数点は切捨てします。");
			}
		} else {
			iLength = DefaultLength;
		}

		iDot	= iLength;
		//付点
		while((cData = cRead()) == '.'){
			iMod = (iDot & 0x01);
			iDot >>= 1;
			if(iMod != 0){
				Warning(L"付点の計算で割り切れませんでした。小数点は切捨てします。");
			}
			iLength += iDot;
		};
		Back();							//StreamPointerAdd(-1);



	//Tick
	} else if (cData == '%'){
		iLength = GetInt();

	} else {
		iLength = -1;
	}

	return(iLength);
}

//==============================================================
//			音長読み込み
//--------------------------------------------------------------
//	●引数
//			int		記載がない場合の音長[tick]
//	●返値
//			int		読み込んだ数値
//					音長がかかれてない場合は、 -1 を返す。
//==============================================================
int		MMLfile::GetLength(unsigned int DefaultLength)	//
{
	char	cData;				//読み込み用
	int		iLength;			//音長 [tick]
	int		iCalc;
	bool	add;

	//音長読み込み
	iLength = readLength(DefaultLength);
	if(iLength == -1){
		return(iLength);
	}

	//音長の加減算
	cData = cRead();
	while((cData == '+') || (cData == '-')){
		//後で計算する符号のチェック
		if(cData == '+'){
			add = true;
		} else {
			add = false;
		}
		iCalc = readLength(DefaultLength);
		if(iCalc == -1){
			Err(L"音長の加減算値に数値以外が指定されています。");
		}
		if(add == true){
			iLength += iCalc;
		} else {
			iLength -= iCalc;
		}
		cData = cRead();
	};
	Back();							//StreamPointerAdd(-1);

	if((iLength < 1) || (iLength > 255)){
		Err(L"音長は、%1（96）〜%255（1+1+2+8）の間で指定して下さい。255[tick]を超える場合はタイ`&', `^'を使って下さい。");
	}

	return(iLength);
}

//==============================================================
//		コマンドIDの取得
//--------------------------------------------------------------
//	●引数
//		Command_Info*			_command
//		unsigned		int		_size
//	●返値
//		int			コマンドコード　（-1でunknown command）
//==============================================================
int	MMLfile::GetCommandID(const Command_Info _command[], unsigned int _size)
{
	unsigned	int		ptCommand	= tellg();	//現在のファイルポインタを保持しておく。
	unsigned	int		i			= 0;		//走査用
	unsigned	int		j;						//文字列チェック用

	//コマンド文字列のチェック
	while(i < _size){
		StreamPointerMove(ptCommand);
		j = 0;
		do{
			if(_command[i].str[j] == 0){
				return(_command[i].id);
			}
		} while(cRead() == _command[i].str[j++]);
		i++;
	}
	return(-1);
}

//==============================================================
//		エラー処理
//--------------------------------------------------------------
//	●引数
//		const	wchar_t	msg[]	エラーメッセージ
//	●返値
//				無し
//==============================================================
void	MMLfile::Err(const wchar_t msg[])
{
	//現在のファイル名と、行数を表示
	cout << "[ ERROR ] " << nowFile->GetFilename()->c_str() << " (Line = " << nowFile->GetLine() << ") : ";

	//エラー内容を表示
	wcout << msg << endl;

	//異常終了
	exit(-1);
}

//==============================================================
//		ワーニング処理
//--------------------------------------------------------------
//	●引数
//		const	wchar_t	msg[]	ワーニングメッセージ
//	●返値
//				無し
//==============================================================
void	MMLfile::Warning(const wchar_t msg[])
{
	//現在のファイル名と、行数を表示
	cout << "[WARNING] " << nowFile->GetFilename()->c_str() << " (Line = " << nowFile->GetLine() << ") : ";

	//ワーニング内容を表示
	wcout << msg << endl;
}
