#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  "clientca.h"
#include  "certreq.h"
#include <sys/types.h>
#include <sys/socket.h>
#include "QMessageBox"
#include <qtextstream.h>
#include "QFile"
#include <QByteArray>

#define IPADDRESS "192.168.1.102"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ipaddress->setText(IPADDRESS);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::on_pushButton_clicked()
{
    int sockfd;
    int conn_ret;
    struct sockaddr_in servaddr;
    char filename[64];
    char fileInfo[INFOSIZE+1];
    int fsize;
    subjectInfo subject;


    QString str1=ui->username->text();
    char*  ch1;
    QByteArray ba1 = str1.toLatin1();
    ch1=ba1.data();

    QString str2=ui->ipaddress->text();
    char*  ch2;
    QByteArray ba2 = str2.toLatin1();
    ch2=ba2.data();

    QString str3=ui->password->text();
    char*  ch3;
    QByteArray ba3 = str3.toLatin1();
    ch2=ba3.data();


/////// check the info valid or not /////////



/////////////////////////////////////////////

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port	= htons(PORT);
    inet_pton(AF_INET,IPADDRESS, &servaddr.sin_addr);

    if((sockfd = socket(AF_INET, SOCK_STREAM,0 )) == -1){
        perror("SOCKET ERROR");
        exit(EXIT_FAILURE);
    }

    conn_ret = ::connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if(conn_ret == -1){
        perror("CONNECT ERROR");
        QMessageBox::warning(this,"Connect Error","failed to connect to server");
        return 0;
        //exit(EXIT_FAILURE);
    }

    printf("starting...\n");


    setCommonname(&subject,ch1);
    setCountryName(&subject,"CN");
    setStateFullName(&subject,"Beijing");
    setLocalityName(&subject,"24JinYuan");
    setOrganizationName(&subject,"SSPKU");
    setOrganizationalUnit(&subject,"PKU");
    setEmailAddress(&subject,"safeclient@ss.pku.edu.cn");

/*
    QString str2=ui->StateFullName->text();
    char* ch2;
    QByteArray ba2=str2.toLatin1();
    ch2=ba2.data();
    setStateFullName(&subject,ch2);

    QString str3=ui->LocalityName->text();
    char* ch3;
    QByteArray ba3=str3.toLatin1();
    ch3=ba3.data();
    setLocalityName(&subject,ch3);

    QString str4=ui->OrganizationName->text();
    char* ch4;
    QByteArray ba4=str4.toLatin1();
    ch4=ba4.data();
    setOrganizationName(&subject,ch4);

    QString str5=ui->OrganizationalUnit->text();
    char* ch5;
    QByteArray ba5=str5.toLatin1();
    ch5=ba5.data();
    setOrganizationalUnit(&subject,ch5);

    QString str6=ui->Commonname->text();
    char* ch6;
    QByteArray ba6=str6.toLatin1();
    ch6=ba6.data();
    setCommonname(&subject,ch6);

    QString str7=ui->EmailAddress->text();
    char* ch7;
    QByteArray ba7=str7.toLatin1();
    ch7=ba7.data();
    setEmailAddress(&subject,ch7);
*/

    //setCountryName(&subject,"CN");
    //setStateFullName(&subject,"Heilongjiang");
    //setLocalityName(&subject,"24 JinYuan Road");
    //setOrganizationName(&subject,"SSPKU");
    //setOrganizationalUnit(&subject,"Peking University");
    //setCommonname(&subject,"HelloWOrld");
    //setEmailAddress(&subject,"sanpuyouyou@163.com");

    if(subjectCheck(&subject) < 0){
        printf("subject error set!\n");
        return -1;
    }

    genApply(REQNAME,&subject);

    infoDeal(REQNAME,fileInfo);
    printf("fileInfo:%s\n",fileInfo);
    sendInfo(sockfd,fileInfo);
    sendfile(sockfd,REQNAME);

    recvInfo(sockfd,fileInfo);
    printf("recv fileInfo:%s\n",fileInfo);

    infoParse(fileInfo,filename,&fsize);
    printf("recv filename: %s	filesize:%d\n",filename,fsize);
    recvfile(sockfd,"clientCert.pem",fsize);

    //QTextStream(FILE * filename,int IO_ReadOnly);//int mode

    QMessageBox::information(this,"certification apply","successful apply");
    return 0;

    }


//void MainWindow::on_showdetails_clicked()
//{
//    QString string;
//    QFile f("usercert.der");
//    if(f.open(QIODevice::ReadOnly))
//    {
//      QTextStream s(&f);
//      while(!s.atEnd())
//    {
//      string+=s.readLine();
//      string+="\n";
//    }
//      //this->ui->details->setText (string);
//    }
//    f.close();
//}
