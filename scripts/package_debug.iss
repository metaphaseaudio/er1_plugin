; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define PluginName "ER-1 Plug-in"
#define PluginVersion "1.0"
#define PluginPublisher "Metaphase"
#define PluginURL "https://www.metaphaseaudio.com/"
#define PluginHash "4d76cab4-ab27-de0e-40fc-91f22a87eb8" ; str(uuid.UUID(bytes=md5(<publisher+name+version>.encode()).digest())

#define VST3BuildPath "C:\Users\Matt\code\er1_plugin\cmake-build-debug\ER-1_artefacts\Debug\VST3\ER-1.vst\*"
#define PresetsBuildPath "C:\Users\Matt\code\er1_plugin\src\install_extras\presets\*"

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={#PluginHash}
AppName={#PluginName}
AppVersion={#PluginVersion}
;AppVerName={#PluginName} {#PluginVersion}
AppPublisher={#PluginPublisher}
AppPublisherURL={#PluginURL}
AppSupportURL={#PluginURL}
AppUpdatesURL={#PluginURL}
DefaultDirName={autocf}\Metaphase
DefaultGroupName={#PluginName}
DisableProgramGroupPage=yes
; Uncomment the following line to run in non administrative install mode (install for current user only.)
;PrivilegesRequired=lowest
OutputBaseFilename="Install {#PluginName} {#PluginVersion}"
Compression=lzma
SolidCompression=yes
WizardStyle=modern
DisableDirPage=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"                                                   

[Files]
Source: "C:\Users\Matt\code\er1_plugin\cmake-build-debug\ER-1_artefacts\Debug\VST3\ER-1.vst3\*"; DestDir: "{code:GetVST3Dir}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:\Users\Matt\code\er1_plugin\src\install_extras\presets\*"; DestDir: "{code:GetPresetDir}"; Flags: ignoreversion recursesubdirs createallsubdirs
;Source: "C:\Users\Matt\code\er1_plugin\cmake-build-debug\ER-1_artefacts\Debug\VST3\ER-1.vst3\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{cm:UninstallProgram,{#PluginName}}"; Filename: "{uninstallexe}"


[Components]
Name: "VST3"; Description: "VST-3 Plug-in"; Types: full
Name: "Presets"; Description: "Preset files"; Types: full


[Code]
var
  VST3DirPage: TInputDirWizardPage;
  PresetDirPage: TInputDirWizardPage;
  DefaultCommonFiles: String;

procedure InitializeWizard;
begin
  { create a directory input page }  
  PresetDirPage := CreateInputDirPage(wpSelectComponents, 'Caption', 'Description', 'SubCaption', False, '');
  VST3DirPage := CreateInputDirPage(wpSelectComponents, 'Caption', 'Description', 'SubCaption', False, '');
  
  { add directory input page items }
  VST3DirPage.Add('VST-3 Installation Path');
  PresetDirPage.Add('Preset Installation Path');
  
  VST3DirPage.Values[0] := GetPreviousData('VST3Dir', ExpandConstant('{autocf64}/VST3'))
  PresetDirPage.Values[0] := GetPreviousData('PresetDir', ExpandConstant('{autodocs}/metaphase/er_1'))  
end;


function ShouldSkipPage(PageID: Integer): Boolean;
begin
  { initialize result to not skip any page (not necessary, but safer) }
  Result := False;
  { if the page that is asked to be skipped is your custom page, then... }
  if PageID = VST3DirPage.ID then
    { if the component is not selected, skip the page }
    Result := not IsComponentSelected('VST3');
  if PageID = PresetDirPage.ID then
    { if the component is not selected, skip the page }
    Result := not IsComponentSelected('Presets');
end;

function GetVST3Dir(Param: String): String;
begin
  Result := VST3DirPage.Values[0];
end;

function GetPresetDir(Param: String): String;
begin
  Result := PresetDirPage.Values[0];
end;
