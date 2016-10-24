node ('pigaco-builder') {
    stage 'Build'
    git url: 'https://github.com/pigaco/libpiga.git'
    dir('build') {
        sh '''cmake -DBUILD_TESTS=on -DENABLE_COVERAGE=on -DCMAKE_INSTALL_PREFIX=local/ ..
        make
        make package'''
        archive '*.deb'
    }
}
