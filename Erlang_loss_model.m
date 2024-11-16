%% Clean up workspace
clearvars;
close all;
clc;

%% Parameters
numberOfChannels = 7:7:70;
trafficLoad = logspace(-1, 2, 1000);

%% Calculations
prBlocking = zeros(length(trafficLoad), length(numberOfChannels));

for i = 1:length(trafficLoad)
    for j = 1:length(numberOfChannels)
        prBlocking(i,j) = ErlangBBlockingProbability(trafficLoad(i), numberOfChannels(j));
    end
end

%% Plots 
figure();
plot(trafficLoad, prBlocking);
grid on;
title('Erlang-B loss model');
xlabel('Traffic load [Erl]');
ylabel('Blocking probability [-]');
xlim([0 max(trafficLoad)]);
ylim([0 1]);
legend(arrayfun(@(nChannels) sprintf('N = %d', nChannels), numberOfChannels, 'UniformOutput', false), 'Location', 'southeast')

figure();
loglog(trafficLoad, prBlocking);
grid on;
title('Erlang-B loss model (log scale)');
xlabel('Traffic load [Erl]');
ylabel('Blocking probability [-]');
xlim([0 max(trafficLoad)]);
ylim([1e-6 1e-1]);
legend(arrayfun(@(nChannels) sprintf('N = %d', nChannels), numberOfChannels, 'UniformOutput', false), 'Location', 'northwest')

%% Functions
function blockingProbability = ErlangBBlockingProbability(trafficLoad, numberOfChannels)
    blockingProbability = (trafficLoad.^numberOfChannels)./(factorial(numberOfChannels)) ./ ...
                          sum(trafficLoad.^(0:numberOfChannels)./factorial(0:numberOfChannels));
end

