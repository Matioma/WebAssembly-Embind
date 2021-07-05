#!/bin/bash

# EMSDK enviroment file path
emsdk_shFile="./../../emsdk_env.sh"

#output directory for Wasm File
output_directory="./Engine/dist/"
output_fileName="Renderer.js"

#list of files to compile
filesToCompile=(
"./Engine/Renderer/RendererAPI.cpp" 
"./Engine/Renderer/Material.cpp"
"./Engine/Renderer/Mesh.cpp" 
"./Engine/Math/Vector3.cpp"
"./Engine/Math/Matrix4.cpp")


t="emcc --bind -o ${output_directory}${output_fileName} ${filesToCompile[*]} -s ALLOW_MEMORY_GROWTH=1 -s USE_WEBGL2=1 -s FULL_ES3=1 -s WASM=1 -s NO_EXIT_RUNTIME=1 -std=c++1z"


while getopts ":sb" option;
do
	case $option in
	s)
		echo setting up the environment
		source ${emsdk_shFile}
		;;
	b)
		eval ${t}
		;;
	*)
		echo "invalid option $OPTARG"
	;;
	esac
done

