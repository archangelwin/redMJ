@set path=E:\Program Files\Microsoft Visual Studio .NET 2003\Common7\IDE;%path%

@cls
copy "�����ļ�\GlobalDef.h" "(��Ϸ���)\Include"

devenv "�������\��������\ComService.vcproj" /build release
devenv "�������\����ؼ�\SkinControls.vcproj" /build release
devenv "�������\�������\SocketModule.vcproj" /build release




devenv "�ͻ������\�ͻ��˹���\ClientShare.vcproj" /build release
devenv "�ͻ������\�ŵ�ģ��\ChannelModule.vcproj" /build release
devenv "�ͻ������\��ϵ����\Companion.vcproj" /build release
devenv "�ͻ������\ͷ�����\UserFace.vcproj" /build release
devenv "�ͻ������\�������\DownLoad.vcproj" /build release
devenv "�ͻ������\��Ϸ�ȼ�\GameRank.vcproj" /build release

devenv "�ͻ������\��Ϸ�㳡(����)\GamePlaza.vcproj" /build release
devenv "�ͻ������\��Ϸ���(����)\GameFrame.vcproj" /build release

