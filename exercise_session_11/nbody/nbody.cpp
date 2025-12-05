#include <random>
#include <vector>
using std::vector;

struct particles {
    vector<float> x, y, z;	// position
    vector<float> vx, vy, vz;	// velocity
    vector<float> ax, ay, az;	// acceleration
};


// Initial conditions
void ic(particles &plist, int n) {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<float> dis(0.0, 1.0);

    plist.x.resize(n);
    plist.y.resize(n);
    plist.z.resize(n);

    plist.vx.resize(n, 0.0f);
    plist.vy.resize(n, 0.0f);
    plist.vz.resize(n, 0.0f);
    plist.ax.resize(n, 0.0f);
    plist.ay.resize(n, 0.0f);
    plist.az.resize(n, 0.0f);
    
	for( int i = 0; i < n; ++i) {
        plist.x[i] = dis(gen);
        plist.y[i] = dis(gen);
        plist.z[i] = dis(gen);
    }

}

void forces(particles &plist) {
    int n = plist.x.size();
    
    for(int i = 0; i < n; ++i) {
        plist.ax[i] = 0.0f;
        plist.ay[i] = 0.0f;
        plist.az[i] = 0.0f;
    }

  
    for(int i = 0; i < n; ++i) {       
        for(int j = 0; j < n; ++j) {    
            if (i == j) continue; 
            
           
            auto dx = plist.x[j] - plist.x[i];
            auto dy = plist.y[j] - plist.y[i];
            auto dz = plist.z[j] - plist.z[i];
            
       
            auto r_sq = dx*dx + dy*dy + dz*dz;
            auto r = sqrtf(r_sq);
            
          
            auto ir3 = 1.0f / (r * r_sq); 
            
            
            plist.ax[i] += dx * ir3;
            plist.ay[i] += dy * ir3;
            plist.az[i] += dz * ir3;
        }
    }
}
int main(int argc, char *argv[]) {
    int N=50'000;
    particles plist;
    ic(plist,N);
    forces(plist);
    return 0;
}
