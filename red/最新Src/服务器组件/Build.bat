@set path=E:\Program Files\Microsoft Visual Studio .NET 2003\Common7\IDE;%path%

@cls

devenv "��½������\LogonServer.vcproj" /build release
devenv "����װ����\ServiceLoader.vcproj" /build release
devenv "�б����\ListService.vcproj" /build release
devenv "�ں����\ServerKernel.vcproj" /build release
devenv "��Ϸ����\GameService.vcproj" /build release
devenv "���ķ�����\CenterServer.vcproj" /build release

