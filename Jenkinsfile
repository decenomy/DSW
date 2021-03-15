pipeline {

    agent any

    environment {
        NAME = 'CryptoFlow'
        BASE_NAME = 'cryptoflow'
        ZIP_NAME = 'CFL'
    }

    stages {

        stage("depends") {

            steps {
                echo 'building depends ...'
                sh '''#!/bin/bash
                    cd depends
                    make -j $(nproc) HOST=x86_64-pc-linux-gnu
                    make -j $(nproc) HOST=x86_64-w64-mingw32
                '''
            }
        }

        stage("build_linux") {

            steps {
                echo 'building linux ...'
                sh '''#!/bin/bash
                    make clean
                    ./autogen.sh
                    ./configure --enable-glibc-back-compat --prefix=$(pwd)/depends/x86_64-pc-linux-gnu LDFLAGS="-static-libstdc++" --enable-cxx --enable-static --disable-shared --disable-debug --disable-tests --disable-bench --with-pic CPPFLAGS="-fPIC -O3" CXXFLAGS="-fPIC -O3"
	                make -j $(nproc) HOST=x86_64-pc-linux-gnu
                '''
            }
        }

        stage("deploy_linux") {

            steps {
                echo 'deploy linux ...'

                sh """#!/bin/bash
                    mkdir -p deploy/linux
                    cp src/${BASE_NAME}d src/${BASE_NAME}-cli src/${BASE_NAME}-tx src/qt/${BASE_NAME}-qt deploy/linux/
                    cd deploy/linux
                    zip ${ZIP_NAME}-\$(git describe --abbrev=0 --tags | sed s/v//)-Linux.zip ${BASE_NAME}d ${BASE_NAME}-cli ${BASE_NAME}-tx ${BASE_NAME}-qt
                    rm -f ${BASE_NAME}d ${BASE_NAME}-cli ${BASE_NAME}-tx ${BASE_NAME}-qt
                """
            }
        }
    }
}