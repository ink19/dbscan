function [] = echo_image(input_filename, output_image)
    a = csvread(input_filename);
    set(0,'DefaultFigureVisible', 'off')
    im = scatter(a(:, 1), a(:, 2),'filled','cdata', a(:, 3));
    saveas(im, output_image, 'jpg');
exit