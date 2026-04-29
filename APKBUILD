# originally an Alpine package, but isn't Arch the same format?

# Contributor:
# Maintainer: Matthew Brewer <mjbrewer17@gmail.com>
pkgname=ghg
pkgver=1.0.3
pkgrel=0
pkgdesc="Play games on heaphones with volume buttons. Games can be programmed with JSON instructions."
url=("https://github.com/matthew-james-brewer/ghg")
arch=("x86_64" "i686" "aarch64" "armv7h")
license=("MPL-2.0")
depends=("cjson" "espeak-ng" "alsa-lib")
makedepends=()
checkdepends=()
install=()
subpackages=()
#source=$pkgver.tar.gz
source=("https://github.com/matthew-james-brewer/ghg/archive/refs/tags/$pkgver.tar.gz")
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

sha512sums="2a318b356d16ed7e46e74969d3bfc134579ba934fc695addcc58653ef536260a6b928407501618d8865102a09bcc398a42859af6aeb3f02a115c71be4d37ad58 $pkgver.tar.gz"
