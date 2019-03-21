#include <fstream>
#include <iostream>
using namespace std;

class treeNode                                      //�����
{
public:
  char* data;                                       //���ݸ�ʽ www��.taobao   ����  0.0.0.0
  treeNode* left;
  treeNode* right;
};

class binTree                                       //IP�������������ֵܱ�ʾ��������bool����ʱTRUE���ǳɹ�������ʧ��
{
public:                                             //�ⲿ�����ӿ�
  binTree()
  {
  }
  bool Initialize();                                //��IP���ݿ��ȡ���ݣ����γ�IP��������IP�����ڵ����ڶ�������������
  char* searchIP(string website);                   //����IP������Ϊ��վ���ƣ����磺www.taobao.com
  void edit(string IP,string websiteWithoutIP);     //�����Ƿ���ڸ���վ�����򲻽��б༭
  bool addNew(string input);                        //����֤�����Ƿ���ȷ��Ȼ���������վ����IP�������������ݿ�
  void destory()
  {
    destoryNodes(root);
  }
  ~binTree()
  {
  }
  bool initalFlag;
private:                                                                       //�ڲ���װ�����ͳ�Ա
  void addNewWebsite(string website);                                          //��������ݵ�������������Ϊ��IP����ַ���ƣ����磺www.cau.edu.cn/0.0.0.0
  bool writeToFile(string websiteWithIP);                                      //����IP��ַ����ַ����д���ļ�β��
  bool editIP(string IP,char*& dataPointer,string websiteWithoutIP);           //�༭������վ��IP���ݣ������ֱ���IP,ָ��IP��ָ�룬�͸���վ������
  treeNode* insertNode(treeNode*& head,const char* data);                      //��HEAD��ָ��ָ��ĺ������������Ϊdata�Ľ�㣬������������
  void spiltWebsite(string& website,string* IPaddress,string* domain);         //������IP��վ���ݷֳ�IP���ݣ��͸���С������磺www.taobao.com/0.0.0.0�ֳ�0.0.0.0��IPADDRESS��www��.taobao��.com��domain string ����
  treeNode* searchParts(const char* part,treeNode* level,char*& lastPointer);  //����PART��ָ������ݣ���.com����levelΪ���������ڵĲ㼶��lastpointer���漰���ӽ���ip����ʱ���Ÿ�ֵ��һ��Ϊnull
  bool checkStringFormat(string toBeChecked,bool whetherHasIP,bool IPpart);    //���string�����Ƿ����IP��ʽ����վ���ƻ��IP����վ����
  void destoryNodes(treeNode*& current);                                       //ɾ�����������н���Լ�����
  treeNode* root;                                                              //����㣬���������ݡ�����ָ��IP������
};


bool binTree::Initialize()
{
  root=new treeNode;
  root->data=new char[11];
  strcpy(root->data,"SystemHead");
  fstream manipulate;
  string website;
  char buffer[100];
  manipulate.open("IPDB.txt",ios::in);
  if (manipulate.is_open())
  {
    while (!manipulate.eof())
    {
      manipulate.getline(buffer,100,'\n');
      website=buffer;
      addNewWebsite(website);
    }
    manipulate.close();
    initalFlag=true;
    return true;
  }
  else
  {
    cout<<"Fail to load data to read."<<endl;
    manipulate.close();
    initalFlag=false;
    return false;
  }
}


bool binTree::addNew(string input)
{
  if (checkStringFormat(input,true,NULL))
  {
	  addNewWebsite(input);
	  return writeToFile(input);
  }
  else
  {
    cout<<"Fail to add"<<input<<endl;
    return false;
  }
}
bool binTree::writeToFile(string websiteWithIP)
{
  fstream writeFile("IPDB.txt",ios::out|ios::app);
  if (writeFile.is_open())
  {
    const char* toBeSaved=websiteWithIP.c_str();
    writeFile.write(toBeSaved,strlen(toBeSaved)*sizeof(char));
    writeFile<<endl;//��Ҫ����"\n"
    writeFile.close();
    return true;
  }
  else
  {
    writeFile.close();
    cout<<"Can't open the file to write."<<endl;
    return false;
  }
}
char* binTree::searchIP(string website)
{
  string domain[4];
  const char* parts[4];
  spiltWebsite(website,NULL,domain);
  for (int i=0;i<4;++i)
  {
    parts[i]=domain[i].c_str();
  }
  int count=strlen(parts[3])?4:3;
  bool flag;
  char* lastPointer="null";
  treeNode* temp=root;
  while (count--)
  {
    temp=searchParts(parts[count],temp,lastPointer);
    if (temp==NULL)
    {
      return NULL;
    }
  }
  return lastPointer;
}
void binTree::edit(string IP,string websiteWithoutIP)
{
  char * data=NULL;
  data=searchIP(websiteWithoutIP);
  if (data!=NULL && editIP(IP,data,websiteWithoutIP))
  {
    return;
  }
  cout<<"�޸���վ���޷��༭���߸�ʽ����"<<endl;
}
void binTree::addNewWebsite(string website)
{
  string IPaddress;
  string domain[4];
  spiltWebsite(website,&IPaddress,domain);
  int count=domain[3].length()?4:3;//���������
  treeNode* current=root;
  for (int i=count-1;i>=0;--i)
  {
    const char* temp=domain[i].c_str();
    current=insertNode(current,temp);
  }
  char* content=new char[IPaddress.length()+1];
  for (  i=0;i<=IPaddress.length();++i)
  {
    content[i]=IPaddress[i];
  }
  current->left=new treeNode(content);
}
treeNode* binTree::insertNode(treeNode*& head,const char* data)
{
  treeNode* child=head;
  if (child->left!=NULL)//����Ϊ�ձ�ʾhead����û������
  {
    child=child->left;//������ڣ������head�����к���
    if (!strcmp(child->data,data))//�Ƚ��ַ������ݣ�ƥ��ɹ�����0,����!0=1
    {
      return child;
    }
    while (child->right!=NULL && strcmp(child->right->data,data))//��ƥ���������
    {
      child=child->right;
    }
    if (child->right == NULL)//����ʧ�ܣ����½�
    {
      child->right=new treeNode;
      child->right->data=new char[strlen(data)+1];
      strcpy(child->right->data,data);
      return child->right;
    }
    else
    {
      return child->right;
    }
  }
  else
  {
    child->left=new treeNode;
    child->left->data=new char[strlen(data)+1];
    strcpy(child->left->data,data);
    return child->left;
  }
}

void binTree::spiltWebsite(string& website,string* IPaddress,string* domain)
{
  int position=website.find_first_of('/');
  string ip;
  if (position!=-1)//��ֹ����Ŀո��´���
  {
    ip=website.substr(position+1,website.length()-position);//IPADDRESS
    website.erase(position,ip.length()+1);//ɾ��IP��ַ����
    if (IPaddress!=NULL)
    {
    	//IP��ַ
      *IPaddress=ip;
    }
  }
    //���滹�Ƿ���website
    int count=0;
    int j=0;//i means begin and j means the end
    unsigned int i=j;
    while (1)
    {
      for (;i<website.length() && website[i]!='.';++i);
      domain[count]=website.substr(j,i-j);
      if (i==website.length())//���һ�θ�ֵ���return
      {
        return;
      }
      j=i;
      ++i;//������һ��ѭ��׼��
      ++count;
    }

}

treeNode* binTree::searchParts(const char* part,treeNode* level,char*& lastPointer)
{
  treeNode* current=level->left;
  if (current==NULL)
  {
    return NULL;
  }
  while (strcmp(current->data,part) && current->right!=NULL )
  {
    current=current->right;
  }
  if (!strcmp(current->data,part))
  {
    if (lastPointer!=NULL)
    {
      for (int i=0;i<strlen(current->data);++i)
      {
        if (current->data[i]=='.')
        {
          return current;
        }
      }
      lastPointer=current->left->data;
    }
    return current;
  }
  return NULL;
}
bool binTree::checkStringFormat(string toBeChecked,bool whetherHasIP,bool IPpart)
{
  if (!whetherHasIP)
  {
    if (toBeChecked[0]=='.'||toBeChecked[toBeChecked.length()-1]=='.')
    {
      return false;
    }
    for (int i=1;i<toBeChecked.length()-1;++i)
    {
      bool flag=isalpha(toBeChecked[i])&&!IPpart;
      if (isdigit(toBeChecked[i])||flag)
      {
        continue;
      }
      else if(toBeChecked[i]=='.')
      {
        if (toBeChecked[i-1]=='.'||toBeChecked[i+1]=='.')
        {
          return false;
        }
      }
      else
      {
        return false;
      }
    }
    return true;
  }
  else
  {
    int interval=toBeChecked.find_first_of('/');
    if (interval!=-1)
    {
	    int length2=toBeChecked.length()-interval;
	    return checkStringFormat(toBeChecked.substr(0,interval),false,false)&&
	      checkStringFormat(toBeChecked.substr(interval+1,length2),false,true);
    }
    return false;
  }
}
void binTree::destoryNodes(treeNode*& current)
{
  if (current->left!=NULL)
  {
    destoryNodes(current->left);
  }
  if (current->right!=NULL)
  {
    destoryNodes(current->right);
  }
  if (current->data!=NULL)
  {
    delete[] current->data;
  }
  delete current;
}


bool binTree::editIP(string IP,char*& dataPointer,string websiteWithoutIP)
{
  if (checkStringFormat(IP,false,true))
  {
    delete[] dataPointer;//�༭�����Ȱ�ԭ������ɾ�����ٴ����µ�
    dataPointer=new char[IP.length()+1];
    strcpy(dataPointer,IP.c_str());
    string fullWebsite=websiteWithoutIP+'/'+IP;
    writeToFile(fullWebsite);
    return true;
  }
  else
  {
    return false;
  }
}

int main()
{
  binTree domainTree;
  const char str[]="1.IP��������ʼ�� 2.����IP  3.��������� 4.�༭IP  5.���ٶ����� 6.�˳����� ";
  string websiteWithoutIP,websiteWithIP,newIP;
  char whetherDestory;
  bool result;
  char* output;
  while (true)
  {
    cout<<str<<endl;
    char option;
    cin>>option;
	  switch (option)
	  {
	  case '1':
	    if (!domainTree.initalFlag)
	    {
	    	result=domainTree.Initialize();
        if (result==false)
        {
          cout<<"�Ҳ�������������DNS����"<<endl;
        }
	    }
      else
      {
        cout<<"�Ҳ�������������DNS����"<<endl;
      }
	  	break;
	  case '2':
      if (domainTree.initalFlag)
      {
	      cout<<"��������ַ������: www.tsinghua.edu.cn"<<endl;
		    cin>>websiteWithoutIP;
		    output=domainTree.searchIP(websiteWithoutIP);
        if (output!=NULL)
        {
          cout<<output<<endl;
        }
        else
        {
          cout<<"�Ҳ�������������DNS����"<<endl;
        }
      }
      else
      {
        cout<<"�Ҳ�������������DNS����"<<endl;
      }
	    break;
	  case '3':
      if (domainTree.initalFlag)
      {
	      cout<<"��������ַ��IP,����: www.tsinghua.edu.cn/166.111.9.2"<<endl;
		    cin>>websiteWithIP;
		    result=domainTree.addNew(websiteWithIP);
        if (result==false)
        {
          cout<<"�Ҳ�������������DNS����"<<endl;
        }
      }
      else
      {
        cout<<"wrong command"<<endl;
      }
	    break;
	  case '4':
      if (domainTree.initalFlag)
      {
	      cout<<"������һ��IP������: 166.111.9.2"<<endl;
		    cin>>newIP;
	      cout<<"������һ����ַ������: www.tsinghua.edu.cn"<<endl;
	      cin>>websiteWithoutIP;
		    domainTree.edit(newIP,websiteWithoutIP);
      }
      else
      {
        cout<<"�Ҳ�������������DNS����"<<endl;
      }
	    break;
	  case '5':
      if (domainTree.initalFlag)
      {
	      cout<<"are you sure to destory the domain tree? Y or N"<<endl;
	      cin>>whetherDestory;
	      if (whetherDestory=='Y'||whetherDestory=='y')
	      {
	        domainTree.destory();
          domainTree.initalFlag=false;
	      }
      }
      else
      {
        cout<<"�Ҳ�������������DNS����"<<endl;
      }
	    break;
	  case '6':
      if (domainTree.initalFlag)
      {
      	domainTree.destory();
      }
	    return 0;
      break;
    default:
      cout<<"�Ҳ�������������DNS����"<<endl;
	  }
  }
}
