# originally an Alpine package, but isn't Arch the same format?

# Contributor:
# Maintainer: Matthew Brewer <mjbrewer17@gmail.com>
pkgname=ghg
pkgver=1.0.6
pkgrel=0
pkgdesc="Play games on heaphones with volume buttons. Games can be programmed with JSON instructions."
url="https://github.com/matthew-james-brewer/ghg"
arch=("x86_64" "i686" "aarch64" "armv7h")
license=("MPL-2.0")
depends=("cjson" "espeak" "alsa-lib")
makedepends=()
checkdepends=()
install=
subpackages=()
#source=$pkgver.tar.gz
source=("https://github.com/matthew-james-brewer/ghg/releases/download/$pkgver/$pkgver-$pkgname.tar.gz")
builddir="$srcdir/"
options=()

build() {
 cd $pkgname-$pkgver
 cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -B b -DCMAKE_INSTALL_PREFIX="$pkgdir/usr"
 cmake --build b
}

package() {
 cd $pkgname-$pkgver
 cmake --install b
}

sha512sums=("1f85cdb6cbf86f4a8ac94501c27afda4ba29b917dc587d0326e2c4ff1d0a41f548c885e36485f2cfebf56dc62e2d204b7fee544ab0b3af333127448ab296c4a0")
