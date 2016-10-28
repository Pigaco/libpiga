node ('pigaco-builder') {
    stage 'Build'
    git url: 'https://github.com/pigaco/libpiga.git'
    dir('build') {
        // Remove the build directory.
        deleteDir

        stage 'Build'
        sh '''cmake -DBUILD_TESTS=on -DENABLE_COVERAGE=on -DCMAKE_INSTALL_PREFIX=local/ ..
        make'''
        
        stage 'Create Package'
        sh 'make package'

        // Stash the package to receive it on the server.
        stash '*.deb'
    }
}

node ('repo') {
    // This node should hold the 3 aptly-repositories used for pigaco development:
    //    pigaco_dev        Development packages.
    //    pigaco_testing    Packages in testing (manual QA).
    //    pigaco            Stable packages ready for publishing.

    stage 'Add package to repository'

    // Receive the package.
    unstash '*.deb'

    // Upload the package into the according repository.
    if(${env.BRANCH_NAME} == "master") {
        sh '''aptly repo add pigaco_dev "*.deb"'''
    } else if(${env.BRANCH_NAME} == "testing") {
        sh '''aptly repo add pigaco_testing "*.deb"'''
    } else if(${env.BRANCH_NAME} == "stable") {
        sh '''aptly repo add pigaco "*.deb"'''
    }

    // The old package archive is no longer needed. It will be deleted.
    stage 'Delete .deb'
    rm '''"*.deb"'''
}
