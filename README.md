# 3DTPortfolio
DX11 라이브러리와 PhysX를 사용한 3D게임 폴가이즈 모작입니다.
영상링크
https://youtu.be/c6LxyqUI7Dc

프로젝트 실행방법---<br/>
0. Level5/GameApp 프로젝트를 시작 프로젝트로 설정<br/>
1. DirectX/GameEngineCore/ThirdParty/bin 에서 프로필에 맞는 폴더(Debug, Release)를 선택하여, 내부에 있는 .zip 압축파일을 같은 폴더에 해제<br/>
2. 타이틀 화면에서 로비 화면으로 넘어가는 키는 Enter<br/>
3. 싱글 플레이의 경우, 하단의 IMGUI 인터페이스에서 원하는 레벨을 클릭하여 이동<br/>
4. 멀티 플레이의 경우, 우측의 IMGUI 인터페이스에서 이름과 색상을 선택<br/>
4-0. 'DirectX/GameEngineContents/ConstantStringSet.h' 파일에서 #define IP_HOST에 정의되어있는 IP주소를 호스트의 IP주소로 변경.<br/>
4-1. 호스트의 경우, 호스트 체크 박스를 선택하고 플레이 버튼을 먼저 클릭하여 서버를 열어야 함.<br/>
※호스트 1인으로 플레이하는 것은 불가<br/>
4-2. 클라이언트의 경우, 호스트의 서버가 열린것을 확인하고 플레이버튼을 클릭하여 서버로 입장.<br/>
성공적으로 서버로 입장했다면 화면에 표시되는 접속자 수가 증가함<br/>
4-3. 모든 클라이언트가 접속했다면 호스트가 우측 IMGUI 인터페이스에서 게임시작 버튼을 클릭하는 것으로 게임 시작.<br/>
