function a = untitled()

A = [11 22 33 44 55 66 77 88 99 100 110 120 130 140 150 222222221 222222222];
c = uint64(333333333);


k = size(A,2);
v = uint64(c);
v = pow(v, k - 1);
disp(v);

for i=2:k
    B = nchoosek(A,i-1);
    size(B, 1);
    cnt = 0;
    a = uint64(0);
    for j=1:size(B, 1)
        if sum(B(j, :))<c
           cnt = cnt + 1;
           
           if i == 13
               sum(B(j,:))
           end
           
           b = mod(pow(c - sum(B(j,:)), k-1), 987654321);
           a = a + b;
           a = mod(a, 987654321);
        end
    end
    
    if mod(i,2) == 1
        v = v + a;
        v = mod(v, 987654321);
    else
        v = v + 987654321;
        v = v - a;
        v = mod(v, 987654321);
    end

end

a = v;

end

function v1 = pow(v,k)

v1 = mod(v, 987654321);
for i=1:k
    v1 = v1 * v;
    v1 = mod(v1, 987654321);
end
end



