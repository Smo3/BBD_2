% vertikalus kampas tarp klausytojo ir garso saltinio
elevation = 0;

% Horizontalus kampas tarp klausytojo ir garso saltinio
angle = 45;

%pagrindinis garsas
filename = `StarWars1.wav`;

%nuskaitomas pagrindinis mono garsas
[Y FS BTS] = wavread(filename);

if mod(length(Y), step_cnt) > 0
    ts = Y;
    Y = zeros(floor(length(Y)/step_cnt+1)*(step_cnt), 1);
    for i = 1:length(ts)
        Y(i) = ts(i);
    end
end

% Apskaiciuojamas KIA
[h]=rir(44100, [1 1 1], 15, 0.2, [10 10 2], [5 5 0.1]);

% nurodomas kelias ir formatas iki HRTF deriniu
pt = sprintf(`elev%d/%s`, elevation, angle);

% Abu masyvai uzpildomi nuliais
chR = zeros(length(Y), 1);
chL = zeros(length(Y), 1);

% Nuskaitomi HRTF deriniai
ptL = sprintf(`%sL.wav`, pt);
[hYL hFSL yBTSL] = wavread(ptL);
ptR = sprintf(`%sR.wav`, pt);
[hYR hFSR yBTSR] = wavread(ptR);

% KIA filtras
dataL = conv(hYL,h(:,1));
dataR = conv(hYR,h(:,2));

% HRTF filtras
dataL = conv(hYL,Y);
dataR = conv(hYR,Y);

% Dvieju kanalu suliejimas
S = zeros(length(chL),2);
S(:,1) = dataL;
S(:,2) = dataR;
wavplay(S, FS, 'async');