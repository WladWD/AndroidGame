#include "WriteTextureToRIF.h"
#include "StoreCookieModel.h"
#include "BarrierStore.h"
#include "StoreModel.h"
#include "CollectStore.h"

using namespace std;
int main() 
{

	RIF::WriteTextureToRIF *wttrif = new RIF::WriteTextureToRIF();
	//Resource::StoreModel *mStoreModel = new Resource::StoreModel();
	Resource::StoreCookieModel *mStoreCookieModel = new Resource::StoreCookieModel();
	Resource::BarrierStore *mBarrierStore = new Resource::BarrierStore();
	Resource::CollectStore *mCollect = new Resource::CollectStore();

	wttrif->WriteToRIF("textures\\pipe\\*");
	wttrif->WriteToRIF("textures\\flash\\coffee\\*");
	wttrif->WriteToRIF("textures\\flash\\suggar\\*");
	wttrif->WriteToRIF("textures\\font\\*");
	mStoreCookieModel->Write("models\\cookie\\*");
	//mStoreModel->Write("models\\blade\\*");
	mBarrierStore->Write("models\\blade\\*");
	mBarrierStore->Write("models\\static\\*");

	mCollect->Write("models\\collect\\sugar\\*");
	mCollect->Write("models\\collect\\coffee\\*");

	//https://github.com/g-truc/gli/blob/0.8.2/manual.md
	//http://gli.g-truc.net/0.8.2/index.html

	//D:\\VS2015 Project\\AGame\\AImageConverter\\
		//"textures\\pipe\\");

	delete mCollect;
	delete wttrif;
	//delete mStoreModel;
	delete mStoreCookieModel;
	delete mBarrierStore;

	return 0;
}

/*$(SolutionDir)DirectXTex\$(Configuration)\$(Platform)

$(ProjectDir)$(Configuration)\$(Platform)
$(ProjectDir)$(Configuration)\$(Platform)\TMP*/

/*$(ProjectDir)$(Configuration)\$(Platform)
$(ProjectDir)$(Configuration)\$(Platform)\TMP*/

/*#include <iostream>
#include <Windows.h>
 //https://learnopengl.com/#!Getting-started/Textures
 
 //http://www.cyberforum.ru/win-api/thread899988.html
int main()
{
    using namespace std;
 
    WIN32_FIND_DATAW wfd;
 
    HANDLE const hFind = FindFirstFileW(L"C:\\*", &wfd);
 
    if (INVALID_HANDLE_VALUE != hFind)
    {
        do
        {
            std::wcout << &wfd.cFileName[0] << std::endl;
        } while (NULL != FindNextFileW(hFind, &wfd));
 
        FindClose(hFind);
    }
 
    return 0;
	}*/