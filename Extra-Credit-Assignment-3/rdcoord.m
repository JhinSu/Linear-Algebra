function A = rdcoord(infilename)
%Converts from coordinate to matrix formfid = fopen(infilename, 'rt');

fid = fopen(infilename, 'rt');
if (fid == -1) 
    error('File not found.');
end;

line = fgets(fid);
v = sscanf(line,'%d');
m = v(1);  n = v(2); nz=v(3);

% bogus return

if (nz < 1) 
    return;
end;

% get first line to see if pattern, real, or complex
%
% sscanf() returns a column vector...
%
line = fgets(fid);
A = sscanf(line, '%f');
num_items = size(A,1);
shape = [1 num_items];

T = zeros(nz,num_items);
T(1,:)= A';

% get rest of lines
for i=2:nz,
    line = fgets(fid);
    t = sscanf(line,'%f', num_items);
    T(i,:) =  t';
end

fclose(fid);

% Now construct the sparse matrix...
% pattern only
if (num_items == 2)     
    A = sparse(T(:,1), T(:,2), zeros(nz,1) , m , n);

% real values
elseif (num_items == 3)
	if (max(abs(T(:,3))) == 0.0 )		% really a pattern matrix?
										% if so, convert to nonzero values,
										% otherwise MATLAB will not record
										% sparsity structure information
		A = sparse(T(:,1), T(:,2), ones(nz,1), m , n);
	else
    	A = sparse(T(:,1), T(:,2), T(:,3), m , n);
    end;

% complex values
elseif (num_items == 4)
    A = sparse(T(:,1), T(:,2), T(:,3) + T(:,4)*sqrt(-1), m , n);
end
A=full(A);
display(A);