Result=zeros(60*40,40);
Group1=zeros(40,1);
for k = 1:25
    jpgFilename = strcat('C:\images\eye-closed\eye', num2str(k), '.jpg');
  imageData = imread(jpgFilename);
  J = rgb2gray(imageData);
  
  Result(:,k) = J(:);
  %disp(Result)
  Group1(k)=1; %if eye is closed assign the group label 1
end

for k = 1:15
    jpgFilename = strcat('C:\images\eye\eye', num2str(k), '.jpg');
  imageData = imread(jpgFilename);
  J = rgb2gray(imageData);
 % disp(size(J))
 % disp(k)
  Result(:,(k+25)) = J(:);
end

Sample=zeros(60*40,5);
for k = 43:47
    jpgFilename = strcat('C:\images\eye-closed\eye', num2str(k), '.jpg');
  imageData = imread(jpgFilename);
  
  J = rgb2gray(imageData);
  
  Sample(:,(k-42)) = J(:);
end
%disp(Sample)
SVMStruct = svmtrain(transpose(Result),Group1);
Group = svmclassify(SVMStruct,transpose(Sample));
disp(Group)
%[pc,score,latent,tsquare] = princomp(transpose(Result));
%disp(cumsum(latent)./sum(latent))