#include <iostream>
#include <cstring>
#include <string>
#include <list>
using namespace std;

const int MAX = 256, n = 68;
const int ERROR_STATE = 100;
typedef int state;          
typedef unsigned char *attri; 
typedef unsigned char *token; 
unsigned char *x;             
unsigned int i = 0;           
int table[n][MAX];
int m;
string s[100];
string comment;

void input(){
    freopen("DATA.INP","r",stdin);
	freopen("DATA.OUT","w",stdout);
    cin >> m; cin.ignore(1);
    for(int i=0; i<m; i++) getline(cin,s[i]);
}
void inputcomment(){
    freopen("DATA1.INP","r",stdin);
    //freopen("DATA1.OUT","w",stdout);
    string temp;
    getline(cin,temp);
    i=0;
    while (!temp.empty()){
        i++;
        comment = comment + temp + (char)13;
        getline(cin,temp);
    }
    if(i!=1) comment.pop_back();
}
unsigned char readchar(unsigned char *x, unsigned int i)
{
    if (i < strlen((char *)x))
        return (*(x + i));
    else
        return ('\0');
}
attri attribute(state s)
{
    char *ch;
    ch = new char[100]();
    switch (s)
    {
    case 2:
        strcpy(ch, "so sanh lon hon bang");
        break;
    case 3:
        strcpy(ch, "dich phai");
        break;
    case 4:
        strcpy(ch, "so sanh lon hon");
        break;
    case 6:
        strcpy(ch, "so sanh nho hon bang");
        break;
    case 7:
        strcpy(ch, "dich trai");
        break;
    case 8:
        strcpy(ch, "so sanh nho hon");
        break;
    case 10:
        strcpy(ch, "So sanh khong bang");
        break;
    case 11:
        strcpy(ch, "phu dinh");
        break;
    case 13:
        strcpy(ch, "XOR bu roi gan");
        break;
    case 14:
        strcpy(ch, "gan");
        break;
    case 17:
        strcpy(ch, "cong bang");
        break;
    case 18:
        strcpy(ch, "tang 1");
        break;
    case 19:
        strcpy(ch, "cong");
        break;
    case 21:
        strcpy(ch, "tru bang");
        break;
    case 22:
        strcpy(ch, "giam 1");
        break;
    case 23:
        strcpy(ch, "tru");
        break;
    case 25:
        strcpy(ch, "nhan bang");
        break;
    case 26:
        strcpy(ch, "nhan");
        break;
    case 28:
        strcpy(ch, "chia bang");
        break;
    case 29:
        strcpy(ch, "chia");
        break;
    case 30:
        strcpy(ch, "chia lay du");
        break;
    case 33:
        strcpy(ch, "AND");
        break;
    case 34:
        strcpy(ch, "AND tren bit");
        break;
    case 35:
        strcpy(ch, "AND tren bit roi gan");
        break;
    case 37:
        strcpy(ch, "OR");
        break;
    case 38:
        strcpy(ch, "OR tren bit");
        break;
    case 39:
        strcpy(ch, "OR tren bit roi gan");
        break;
    case 41:
        strcpy(ch, "XOR tren bit roi gan");
        break;
    case 42:
        strcpy(ch, "XOR");
        break;
    case 43:
        strcpy(ch, "NOT tren bit");
        break;
    case 45:
        strcpy(ch, "ten bien");
        break;
    case 47:
        strcpy(ch, "chu thich tren 1 dong");
        break;
    case 50:
        strcpy(ch, "chu thich tren nhieu dong");
        break;
    case 53:
        strcpy(ch, "so nguyen he bat phan");
        break;
    case 56:
        strcpy(ch, "so nguyen he thap luc phan");
        break;
    case 58:
        strcpy(ch, "so nguyen he thap phan");
        break;
    case 59:
        strcpy(ch, "so 0");
        break;
    case 61:
        strcpy(ch, "Loi so bat phan khong co 8|9");
        break;
    case 62:
        strcpy(ch, "Loi so nguyen he thap luc phan chi co (0..9|a..f|A..F)");
        break;
    case 63:
        strcpy(ch, "Loi ten khong bat dau bang chu so");
        break;
    case 66:
        strcpy(ch, "so thuc");
        break;
    default:
        strcpy(ch, "token ko duoc doan nhan(tt ko dung) \0");
    }
    return (attri)ch;
}
int nostar_end_state(state s)
{
    switch (s)
    {
    case 2:
    case 3:
    case 6:
    case 7:
    case 10:
    case 13:
    case 17:
    case 18:
    case 21:
    case 22:
    case 25:
    case 28:
    case 30:
    case 33:
    case 35:
    case 37:
    case 39:
    case 41:
    case 43:
    case 47:
    case 50:
    case 62:
    case 63:
        return 1;
    default:
        return 0;
    }
}
int star_end_state(state s)
{
    switch (s)
    {
    case 4:
    case 8:
    case 11:
    case 14:
    case 19:
    case 23:
    case 26:
    case 29:
    case 34:
    case 38:
    case 42:
    case 45:
    case 53:
    case 56:
    case 58:
    case 59:
    case 61:
    case 66:
        return 1;
    default:
        return 0;
    }
}
void catchar_in_token(unsigned char c, token tk)
{
    *(tk + strlen((char *)tk) + 1) = '\0'; 
    *(tk + strlen((char *)tk)) = c;        
}
token search_token(unsigned int *i, attri tt)
{
    token tk = new unsigned char[100]();
    unsigned char c;
    state s = 0, cs;
    do
    {
        do
        {
            c = readchar(x, *i);
            *i = *i + 1;
        } while ((c == ' ') && (*i < strlen((char *)x)) && s == 0);
        if ((c == ' ') && *i == strlen((char *)x) && s == 0)
        {
            *tk = '\0';
            return tk;
        }
        *i = *i - 1;
        cs = table[s][c];
        if (cs == ERROR_STATE)
        {
            cout << "loi tai vi tri " << *i << "\n\n";
            *tk = '\0';
            break;
        }
        else if (star_end_state(cs))
        {
            strcpy((char *)tt, (char *)attribute(cs));
            break;
        }
        else if (nostar_end_state(cs))
        {
            catchar_in_token(c, tk);
            *i = *i + 1;
            strcpy((char *)tt, (char *)attribute(cs));
            break;
        }
        else if (*i >= strlen((char *)x))
        {
            *tk = '\0';
            break;
        }
        else
        {
            catchar_in_token(c, tk);
            if (c != '\0')
            {
                *i = *i + 1;
            }
            s = cs;
        }
    } while (1);
    return tk;
}
void create_table(int table[n][MAX])
{
    //
    for (int i=0;i<MAX;i++){
        table[0][i] = 100;
    }
    //
    table[0]['>'] = 1;
    table[0]['+'] = 16;
    table[0]['<'] = 5;
    table[0]['-'] = 20;
    table[0]['!'] = 9;
    table[0]['*'] = 24;
    table[0]['='] = 12;
    table[0]['/'] = 27;
    table[0]['%'] = 30;
    table[0]['&'] = 32;
    table[0]['|'] = 36;
    table[0]['^'] = 40;
    table[0]['~'] = 43;
    //
    for (int i=65,j=97;i<=90;i++,j++){
        table[0][i] = 44;
        table[0][j] = 44;
    }
    table[0]['_'] = 44;
    //
    table[0][48] = 51;
    for (int i=49;i<=57;i++){
        table[0][i] = 57;
    }
    table[0]['.'] = 64;
    for (int i = 0; i < MAX; i++)
    {
        //
        table[1][i] = 4;
        table[2][i] = 100;
        table[17][i] = 100;
        table[5][i] = 8;
        table[3][i] = 100;
        table[18][i] = 100;
        table[9][i] = 11;
        table[4][i] = 100;
        table[19][i] = 100;
        table[12][i] = 14;
        table[6][i] = 100;
        table[21][i] = 100;
        table[16][i] = 19;
        table[7][i] = 100;
        table[22][i] = 100;
        table[20][i] = 23;
        table[8][i] = 100;
        table[23][i] = 100;
        table[24][i] = 26;
        table[10][i] = 100;
        table[25][i] = 100;
        table[27][i] = 29;
        table[11][i] = 100;
        table[26][i] = 100;
        table[13][i] = 100;
        table[28][i] = 100;
        table[14][i] = 100;
        table[29][i] = 100;
        table[13][i] = 100;
        table[30][i] = 100;
        //
        table[32][i] = 34;
        table[33][i] = 100;
        table[34][i] = 100;
        table[35][i] = 100;
        table[36][i] = 38;
        table[37][i] = 100;
        table[38][i] = 100;
        table[39][i] = 100;
        table[40][i] = 42;
        table[41][i] = 100;
        table[42][i] = 100;
        table[43][i] = 100;
        //
        table[44][i] = 45;
        table[45][i] = 100;
        //
        table[46][i] = 46;
        table[47][i] = 100;
        table[48][i] = 48;
        table[49][i] = 48;
        table[50][i] = 100;
        //
        table[53][i] = 100;
        table[56][i] = 100;
        table[58][i] = 100;
        table[59][i] = 100;
        table[61][i] = 100;
        table[62][i] = 100;
        table[63][i] = 100;
        table[66][i] = 100;
        table[60][i] = 61;
        table[52][i] = 53;
        table[55][i] = 56;
        table[57][i] = 58;
        table[65][i] = 66;
        table[51][i] = 59;
        table[67][i] = 61;
    }
    //
    table[1]['='] = 2;
    table[1]['>'] = 3;
    table[5]['='] = 6;
    table[5]['<'] = 7;
    table[9]['='] = 10;
    table[12]['='] = 13;
    table[16]['='] = 17;
    table[16]['+'] = 18;
    table[20]['='] = 21;
    table[20]['-'] = 22;
    table[24]['='] = 25;
    table[27]['='] = 28;
    table[32]['&'] = 33;
    table[32]['='] = 35;
    table[36]['|'] = 37;
    table[36]['='] = 39;
    table[40]['='] = 41;
    //
    for (int i=65,j=97;i<=90;i++,j++){
        table[44][i] = 44;
        table[44][j] = 44;
        table[57][j] = 63;
    }
    for (int i=48;i<=57;i++){
        table[44][i] = 44;
    }
    table[44]['_'] = 44;
    //
    table[27]['/'] = 46;
    table[27]['*'] = 48;
    table[46][13] = 47; //Enter
    table[48]['*'] = 49;
    table[49]['*'] = 49;
    table[49]['/'] = 50;
    //
    table[51][56] = 60;
    table[51][57] = 60;
    for (int i=48;i<=57;i++){
        table[54][i] = 55;
        table[57][i] = 57;
        table[64][i] = 65;
        table[65][i] = 65;
        table[55][i] = 55;
        table[60][i] = 60;
        table[67][i] = 67;
    }
    for (int i=48;i<=55;i++){
        table[51][i] = 52;
        table[52][i] = 52;
    }
    table[52][56] = 67;
    table[52][57] = 67;
    table[51]['x'] = 54;
    table[51]['X'] = 54;
    for (int i=65,j=97;i<=70;i++,j++){
        table[54][i] = 55;
        table[54][j] = 55;
        table[55][i] = 55;
        table[55][j] = 55;
    }
    for (int i=71,j=103;i<=90;i++,j++){
        table[55][i] = 62;
        table[55][j] = 62;
    }
    table[51]['.'] = 64;
    table[60]['.'] = 64;
    table[52]['.'] = 64;
    table[57]['.'] = 64;
}
void save_token_and_attribute(token tk, attri a)
{
    string token(reinterpret_cast<char*>(tk));
    string attri(reinterpret_cast<char*>(a));
    cout << token << " | " << attri << "\n";
}

void lexical_analysis()
{
    token tk;
    attri a = new unsigned char[100]();
    do
    {
        tk = search_token(&i, a);
        if(*tk!='\0')
            save_token_and_attribute(tk, a);
    } while ((*tk != '\0') && (i < strlen((char *)x)));
    a = NULL;
}

int main()
{
    input();
    create_table(table);
    for(int j=0;j<m;j++){
        x = new unsigned char[s[j].size()+1]();
        strcpy(reinterpret_cast<char*>(x), s[j].c_str());
        i = 0;
        cout << s[j] << "\n";
        lexical_analysis();
        cout << "\n";
        x = NULL;
    }
    delete[] x;
    //
    inputcomment();
    x = new unsigned char[comment.size()+1]();
    strcpy(reinterpret_cast<char*>(x), comment.c_str());
    i = 0;
    cout << comment << "\n";
    lexical_analysis();
    cout << "\n";
    x = NULL;
    delete[] x;
    return 0;
}