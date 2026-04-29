# originally an Alpine package, but isn't Arch the same format?

# Contributor:
# Maintainer: Matthew Brewer <mjbrewer17@gmail.com>
pkgname=ghg
pkgver=1.0.2
pkgrel=0
pkgdesc="Play games on heaphones with volume buttons. Games can be programmed with JSON instructions."
url="https://github.com/matthew-james-brewer/ghg"
arch=("x86_64" "i686" "aarch64" "armv7h")
license="MPL-2.0"
depends="cjson espeak-ng alsa-lib"
makedepends=""
checkdepends=""
install=""
subpackages=""
#source=$pkgver.tar.gz
source="https://github.com/matthew-james-brewer/ghg/archive/refs/tags/$pkgver.tar.gz"
builddir="$srcdir/"
options="!check"

build() {
 cd $pkgname-$pkgver
 cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -B b -DCMAKE_INSTALL_PREFIX="$pkgdir/usr"
 cmake --build b
}

package() {
 cd $pkgname-$pkgver
 cmake --install b
}

sha512sums="e46a1a9265a8daaf0aeabe0f2b1af033022626953450a3c814ce95cd0ef4f39bd1ad080dd3fb3fafd4bab0b073dff0ee389239e5ca82647481dfef8621d5a2ff $pkgver.tar.gz"
