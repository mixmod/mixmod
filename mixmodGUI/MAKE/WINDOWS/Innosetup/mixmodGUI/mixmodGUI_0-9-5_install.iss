;mixmodGUI.iss

[Setup]
Compression=lzma/max
OutputBaseFilename=mixmodGUI_0-9-5
OutputDir=C:\TEMP
SourceDir=C:\TEMP\mixmodGUI
;AlwaysRestart=yes
AlwaysShowDirOnReadyPage=yes
AppName= mixmodGUI
AppVerName=MixmodGUI version 0.9.5
AppPublisher=INRIA Futurs (Orsay),  Laboratory of Mathematics (Besan�on), Laboratory Heudiasyc (Compi�gne), Laboratory Paul Painlev� (Lille)
AppPublisherURL=http://www.mixmod.org
AppSupportURL=http://www.mixmod.org
AppUpdatesURL=http://www.mixmod.org
DefaultDirName={pf}\mixmodGUI
DefaultGroupName=mixmodGUI
Uninstallable=yes
AppCopyright=Copyright (C) 2001-2011 Mixmod Team : INRIA, CNRS, Universities of Franche-Comte, Compiegne and Lille.
UsePreviousAppDir=no
UsePreviousGroup=no
PrivilegesRequired=poweruser


WizardImageBackColor=$688D6B
WizardImageFile=C:\TEMP\logo_Mixmod.bmp
WizardSmallImageFile=C:\TEMP\logo_Mixmod.bmp


[Code]
Var
  finishedInstall : Boolean;


function adminLogOn():Boolean;
begin
  if IsAdminLoggedOn() then
  begin
    Result:=true;
  end
  else
  begin
    Result:=false;
  end;
end;



function ShouldSkipPage(CurPage: Integer):Boolean;
begin

  case CurPage of
    {current page = select directory of install}
    wpSelectProgramGroup, wpSelectTasks, wpReady, wpPreparing, wpInfoAfter:
    begin

      if finishedInstall then
      begin
        Result:=true;
      end
      else
      begin
        Result:=false;
      end;
    end;

  end;

end;



function NextButtonClick(CurPage: Integer): Boolean;
var
  dirExist : Boolean;
  rep : integer;
begin

  Result := True;

  case CurPage of

    {current page = Info before}
    {--------------------------}
    wpWelcome:
    begin
        if (adminLogOn() = false) then
        begin
          rep := MsgBox('Administrator is not connected : Mixmod will be installed in your own environment (current user)' #13#13 'If you want to install Mixmod for all users, please stop the setup (click to cancel button in the next window)' #13#13 'and restart setup with administrator privileges' , mbInformation, MB_OK);
        end
    end;


    {current page = select directory of install}
    {------------------------------------------}
    wpSelectDir:
    begin

      {test if install directory already exist}
      if (DirExists(WizardDirValue)) then
      begin
        dirExist:=true;
      end
      else
      begin
        dirExist:=false;
      end;
      if (dirExist=true) then
      begin
        rep := MsgBox('Mixmod is already installed in '+WizardDirValue+' directory' #13#13 'Continue in this directory ? (files will be repaced) ' , mbError, MB_OKCANCEL);
        {remplacer l'installation}
        if (rep=IDOK) then
        begin
          DelTree(WizardDirValue, true, true, true);
          Result:=true;
        end
        {revenir � la page precedente}
        else
        begin
          Result := false;
        end;
      end;




      {le r�pertoire n'existe pas, on continue l'installation}
      if (NOT dirExist) then
      begin
      end;

    end;

  end;
end;

    
[Dirs]
Name: "{app}\BIN"; Flags: uninsalwaysuninstall
Name: "{app}\DATA"; Flags: uninsalwaysuninstall
Name: "{app}\MXD"; Flags: uninsalwaysuninstall

[Files]
Source: "*.*"; DestDir : "{app}"; Flags: ignoreversion
Source: "BIN\*.*"; DestDir: "{app}\BIN"; Flags: ignoreversion
Source: "DATA\*.*"; DestDir: "{app}\DATA"; Flags: ignoreversion
Source: "MXD\*.*"; DestDir: "{app}\MXD"; Flags: ignoreversion


[Icons]  
Name: "{group}\Launch MixmodGUI"; Filename: "{app}\BIN\mixmodGUI_exe.exe"
Name: "{group}\License"; Filename: "{app}\License.txt"
Name: "{group}\ReadMe"; Filename: "{app}\ReadMe.txt"
Name: "{group}\{cm:ProgramOnTheWeb,Mixmod}"; Filename: "http://www.mixmod.org"
Name: "{group}\Uninstall"; Filename: "{app}\unins000.exe"



[UninstallDelete]
Type: files; Name: "{app}\BIN\*.txt"
Type: files; Name: "{app}\*.*"
Type: dirifempty; Name: "{app}"
Type: dirifempty; Name: "{groupname}"

