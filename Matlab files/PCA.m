function[Group]= PCA(clsize,opsize,samplesize) % specifies the number of eye closed images and eye open images
G = fspecial('gaussian',[5 5],2);
edgeDetAlgo='sobel';
Directory = fullfile('C:','images','ClosedEyes');
file = dir(fullfile(Directory,'*.jpg'));
clsize=numel(file);
disp(clsize)


Directory = fullfile('C:','images','OpenEyes');
file = dir(fullfile(Directory,'*.jpg'));
opsize=numel(file);
disp(opsize)


Result=zeros(60*40,clsize+opsize);
Group1=zeros(clsize+opsize,1);% a column vector containing classification for the training set

%open the directory of closed eyes
Directory = fullfile('C:','images','ClosedEyes');
file = dir(fullfile(Directory,'*.jpg'));
NF = clsize;
images = cell(NF,1);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for k = 1 : clsize
  images{k} = imread(fullfile('C:','images','ClosedEyes', file(k).name));
  imageData=images{k};
    imageData=imresize(imageData, [60 40]); % resize to our standard size
    
    %disp(file(k).name)
    if(numel(size(imageData))==3)
    J = rgb2gray(imageData);
    else J=imageData;
    end
    J = imfilter(J,G,'same');
    J = histeq(J);
    J=edge(J,edgeDetAlgo);
  Group1(k)=1; %if eye is closed assign the group label 1
  Result(:,k) = J(:); %assignment of image vector to input matrix
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%open the directly of openeyes
Directory = fullfile('C:','images','OpenEyes');
file = dir(fullfile(Directory,'*.jpg'));
NF = opsize;
images = cell(NF,1);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for k = 1:opsize
    images{k} = imread(fullfile('C:','images','OpenEyes', file(k).name));
  imageData=images{k};
  
    imageData=imresize(imageData, [60 40]); % resize to our standard size
    
  % disp(file(k).name)
  if(numel(size(imageData))==3)
    J = rgb2gray(imageData);
    else J=imageData;
  end
  J = imfilter(J,G,'same');
  J = histeq(J);
  J=edge(J,edgeDetAlgo);
 % disp(size(J))
 % disp(k)
  Result(:,(k+clsize)) = J(:); %assignment of image vector to input matrix
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


[Coeff,Score,latent]=princomp(transpose(Result));

%an observation is shown by a row in the matrix


numPrinComp=sum(cumsum(latent)./sum(latent)<=.99);
disp(numPrinComp)
redPcaMat= zeros(2400,numPrinComp);

%22 is the number of principal components
%disp(size(redPcaMat))
%disp(size(Coeff))


for k=1:numPrinComp
redPcaMat(:,k)=Coeff(:,k);   
end


Result=transpose(Result)*redPcaMat; % projecting the image to 22 chosen principal component axis


sampleFile='eye-closed';
Directory = fullfile('C:','images',sampleFile);
file = dir(fullfile(Directory,'*.jpg'));
NF = numel(file);
samplesize=NF;
images = cell(NF,1);

% Creating the sample
Sample=zeros(60*40,samplesize);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for k = 1:samplesize
    images{k} = imread(fullfile('C:','images',sampleFile, file(k).name));
  imageData=images{k};
    imageData=imresize(imageData, [60 40]); % resize to our standard size
    
    
  if(numel(size(imageData))==3)
    J = rgb2gray(imageData);
    else J=imageData;
  end
  J = imfilter(J,G,'same');
  J = histeq(J);
  J=edge(J,edgeDetAlgo);
  %disp(thresh)
  %imwrite(J,fullfile('C:','images','Saved', file(k).name));
  Sample(:,(k)) = J(:);
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


options = optimset('maxiter',1000);
 
SVMStruct = svmtrain(Result,Group1','quadprog_opts',options);

t = cputime;
Group = svmclassify(SVMStruct,transpose(Sample)*redPcaMat); % transforming the sample to pca space
e = cputime-t;
Group=transpose(Group);
disp(e);


disp(sum(Group==0)./size(Group,2))
%disp(cumsum(latent)./sum(latent))