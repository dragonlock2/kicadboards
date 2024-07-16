cmake_minimum_required(VERSION 3.20.0)
project(atlc)

include_directories(
    .
)

add_executable(atlc
    src/atlc.c # main()
    src/calculate_colour_data.c
    src/check_for_shorts.c
    src/do_fd_calculation.c
    src/exit_with_msg_and_exit_code.c
    src/find_electric_fields.c
    src/find_energy_per_metre.c
    src/find_maximum_values.c
    src/finite_difference_single_threaded.c
    src/get_file_pointer_with_right_filename.c
    src/get_options.c
    src/memory.c
    src/print_copyright.c
    src/print_data_for_directional_couplers.c
    src/print_data_for_two_conductor_lines.c
    src/read_bitmap_file_headers.c
    src/set_data_to_sensible_starting_values.c
    src/set_oddity_from_Greens_paper.c
    src/setup_arrays.c
    src/swap_conductor_voltages.c
    src/update_voltage_array.c
    src/usage_atlc.c
    src/write_fields_for_directional_couplers.c
    src/write_fields_for_two_conductor_lines.c
)

add_executable(create_bmp_for_microstrip_coupler
    src/align_bitmap_image.c
    src/check_error.c
    src/check_parameters_of_create_bmp_for_microstrip_coupler.c
    src/convert_create_bmp_for_coupled_microstrip_dimensions_to_integers.c
    src/create_bmp_for_microstrip_coupler.c # main()
    src/exit_with_msg_and_exit_code.c
    src/fill_image_vector_for_create_bmp_for_microstrip_coupler.c
    src/get_Er1_and_Er2_colours.c
    src/get_options.c
    src/memory.c
    src/usage_create_bmp_for_microstrip_coupler.c
    src/write_bitmap.c
    src/write_bitmap_out.c
)

# TODO add rest of executables
