#include<Windows.h>
#include<tchar.h>
#include"Aclapi.h"

BOOL GetProcessIntegrityLevel(HANDLE hProcess, PDWORD pIntegrityLevel, 
   PDWORD pPolicy, PDWORD pResourceIntegrityLevel, PDWORD pResourcePolicy) {
   
   HANDLE hToken = NULL;
   if (!OpenProcessToken(hProcess, TOKEN_READ, &hToken)) {
      return(FALSE);
   }

   BOOL bReturn = FALSE;
   
   // First, compute the size of the buffer to get the Integrity level
   DWORD dwNeededSize = 0;
   if (!GetTokenInformation(
      hToken, TokenIntegrityLevel, NULL, 0, &dwNeededSize)) {

      PTOKEN_MANDATORY_LABEL pTokenInfo = NULL;
      if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
         // Second, allocate a memory block with the the required size 
         pTokenInfo = (PTOKEN_MANDATORY_LABEL)LocalAlloc(0, dwNeededSize);
         if (pTokenInfo != NULL) {
            // And finally, ask for the integrity level
            if (GetTokenInformation(hToken, TokenIntegrityLevel, pTokenInfo, 
               dwNeededSize, &dwNeededSize)) {

               *pIntegrityLevel = 
                  *GetSidSubAuthority(
                     pTokenInfo->Label.Sid, 
                     (*GetSidSubAuthorityCount(pTokenInfo->Label.Sid)-1)
                     );
               bReturn = TRUE;
            }
          
            // Don't forget to free the memory
            LocalFree(pTokenInfo);
         }
      }
   }

   // Try to get the policy if the integrity level was available
   if (bReturn) {
      *pPolicy = TOKEN_MANDATORY_POLICY_OFF;
      dwNeededSize = sizeof(DWORD);
      GetTokenInformation(hToken, TokenMandatoryPolicy, pPolicy, 
         dwNeededSize, &dwNeededSize);
   }
   
   // Look for the resource policy
   *pResourceIntegrityLevel = 0; // 0 means none explicitely set
   *pResourcePolicy = 0;
   
   PACL pSACL = NULL;
   PSECURITY_DESCRIPTOR pSD = NULL;
   DWORD dwResult = ERROR_SUCCESS;
   
   // Look for the no-read-up/no-write-up policy in the SACL
   if (hToken != NULL) {
      dwResult = 
         GetSecurityInfo(
            hProcess, SE_KERNEL_OBJECT,
            LABEL_SECURITY_INFORMATION,
            NULL, NULL, NULL, 
            &pSACL, &pSD
          );
      if (dwResult == ERROR_SUCCESS) {
         if (pSACL != NULL) {
            SYSTEM_MANDATORY_LABEL_ACE* pACE = NULL;
            if ((pSACL->AceCount > 0) && (GetAce(pSACL, 0, (PVOID*)&pACE))) {
               if (pACE != NULL) {
                  SID* pSID = (SID*)(&pACE->SidStart);
                  *pResourceIntegrityLevel = pSID->SubAuthority[0];
                  *pResourcePolicy = pACE->Mask;
               }
            }
         }
      }
      
      // Cleanup memory allocated on our behalf
      if (pSD != NULL) LocalFree(pSD); 
   }


   // Don't forget to close the token handle.
   CloseHandle(hToken);

   return(bReturn);   
}

int _tmain()
{
	DWORD IntegrityLevel,Policy,ResourceIntegrityLevel,ResourcePolicy;

	//第一个参数，是进程句柄，第二个到第五个参数，是四个DWORD类型的指针。
	GetProcessIntegrityLevel(GetCurrentProcess(),&IntegrityLevel,
		&Policy,&ResourceIntegrityLevel,&ResourcePolicy);



	_tprintf(L"IntegrityLevel=%0X\n",IntegrityLevel);
	_tprintf(L"Policy=%0X\n",Policy);
	_tprintf(L"ResourceIntegrityLevel=%0X\n",ResourceIntegrityLevel);
	_tprintf(L"ResourcePolicy=%0X\n",ResourcePolicy);
	_gettchar();


	return 0;
}