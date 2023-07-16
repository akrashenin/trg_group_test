#include <iostream>
#include <string>
#include <sqlite3.h>
#include <fstream>
#include <sstream>

using namespace std;
fstream flOut("test.txt", fstream::out);

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   string strArg;
   stringstream sstrOut;
   stringstream sstrOutTtl;
   static bool flagTitlePrint = false;

   if (!flagTitlePrint && argc != 0)
   {
        sstrOutTtl.clear();
        flagTitlePrint = true;
        for(int i = 0; i<argc; i++){
            cout << azColName[i] << "\t";
            sstrOutTtl << azColName[i] << "\t";
        }
        sstrOut << "\n";
        flOut << sstrOutTtl.str();
        cout << endl;
   }

   sstrOut.clear();
   for(int i = 0; i<argc; i++) {
      strArg = argv[i] ? argv[i] : "NULL";
      cout << strArg << "\t";
      sstrOut << strArg << "\t";
   }
   sstrOut << "\n";
   flOut << sstrOut.str();
   cout << endl;
   return 0;
}

int main(int argc, char *argv[])
{
    cout << "It's work!" << endl;

    string strPath;
    string sql = "select DateTime, OriginZone, DestZone from passenger order by DateTime";
    char *zErrMsg = 0;

    if(argc > 1)
    {
        strPath = argv[1];
        cout << strPath.c_str() << endl;
    }
    else
        strPath = "/home/akrashenin/Projects/CodeBlocks/test_trg_group/test.sq3";

    sqlite3 *pDb;          /* OUT: SQLite db handle */

    int iRes = sqlite3_open(strPath.c_str()/* Database filename (UTF-8) */, &pDb);
    if(!iRes)
        cout << " DB has been opened successfully!" << endl;
    else
        cout << "DB has not been opened successfully! iRes = " << iRes << endl;

    iRes = sqlite3_exec(pDb, sql.c_str(), callback, 0, &zErrMsg);

    if( iRes != SQLITE_OK ){
      cout << "SQL error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   }
   else {
      cout << "Table select successfully!" << endl;
   }

    sqlite3_close(pDb);

    return 0;
}
