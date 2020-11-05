#include "Db.h"
Db::Db(const char* host,const char* schema,const char* user,const char* password){
    db.setHostName(host);
    db.setDatabaseName(schema);
    db.setUserName(user);
    db.setPassword(password);
}
 char* Db::check(){
    if(db.open()){
        return "YES!!!";
    }
    return "NO!!!!";
}
