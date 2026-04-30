# Contributor:
# Maintainer: Matthew Brewer <mjbrewer17@gmail.com>
pkgname=ghg
pkgver=1.0.4
pkgrel=0
pkgdesc="Play games on heaphones with volume buttons. Games can be programmed with JSON instructions."
url="https://github.com/matthew-james-brewer/ghg"
arch="x86_64 i686 aarch64 armv7h"
license="MPL-2.0"
depends="cjson espeak-ng alsa-lib"
makedepends=
checkdepends=
install=
subpackages=
#source=$pkgver.tar.gz
source="https://github.com/matthew-james-brewer/ghg/releases/download/$pkgver/$pkgver-$pkgname.tar.gz"
builddir="$srcdir/"
options="!check"
# idgaf about tests

build() {
 cd $pkgname-$pkgver
 cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -B b -DCMAKE_INSTALL_PREFIX="$pkgdir/usr"
 cmake --build b
}

package() {
 cd $pkgname-$pkgver
 cmake --install b
}

sha512sums="43a042638e2c819d23cb3a5e34bb60986e4489f23bb314ea61f6be2c92fb289c0209786b0dcbf900d9ae5cd820463121b88a99ce81cff1ea1f9e67f0fa354910  $pkgver-$pkgname.tar.gz"
