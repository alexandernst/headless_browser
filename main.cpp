//
// @author Alexander Nestorov <alexandernst@gmail.com>
// 
// @licensed under the WTFPL
//

#include <QApplication>
#include "hb.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    
    HB *hb = new HB();
    hb->_load(QUrl(argv[1]));
    return a.exec();
}
