# Versão mínima do Cmake
cmake_minimum_required(VERSION 3.10)

#Nome do projeto
project(restaurante_proj)

# Definindo C Standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED YES)

# Usando https://github.com/tcbrindle/sdl2-cmake-scripts para incluir SDL2 corretamente
# Especificando um caminho para outros módulos
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake_sdl2")

# Adicionando flags para o compilador
add_definitions(-Wall)

# Incluindo diretórios
include_directories(src)

# Definindo o executável e os arquivos de código fonte a compilar
add_executable(restaurante src/main.c src/fila.c src/lista.c src/opcoes_menu.c src/utils.c

	src/tela_cardapio.c src/tela_ver_cardapio.c src/tela_adicionar_no_cardapio.c src/tela_remover_do_cardapio.c 
  src/tela_pedidos.c src/tela_ver_pedidos.c src/tela_adicionar_nos_pedidos.c src/tela_servir_dos_pedidos.c
  
	src/kiss_sdl/kiss_widgets.c src/kiss_sdl/kiss_draw.c src/kiss_sdl/kiss_general.c)

# Adicionando dependência do SDL
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
					${SDL2_IMAGE_INCLUDE_DIR}
					${SDL2_TTF_INLCUIDE_DIR})
target_link_libraries(restaurante ${SDL2_LIBRARY}
							${SDL2_IMAGE_LIBRARIES}
							${SDL2_TTF_LIBRARIES})

# Copiando os arquivos de recurso do KISS para a pasta da build para que o projeto funcione
add_custom_command(	TARGET restaurante PRE_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${PROJECT_SOURCE_DIR}/kiss_resources $<TARGET_FILE_DIR:restaurante>/kiss_resources)
