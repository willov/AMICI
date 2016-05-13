%
% @file amimodel
% @brief definition of amimodel class
%
classdef amimodel < handle
    % AMIMODEL carries all model definitions including functions and events
    
    properties ( GetAccess = 'public', SetAccess = 'private' )
        % symbolic definition struct @type struct
        sym = struct.empty();
        % struct which stores information for which functions c code needs to be generated @type struct
        fun = struct.empty();
        % struct which stores information for which functions c code needs
        % to be generated @type amievent
        event = amievent.empty();
        % name of the model @type string
        modelname = char.empty();
        % struct that contains hash values for the symbolic model definitions @type struct
        HTable = struct.empty();
        % flag indicating whether debugging symbols should be compiled @type bool
        debug = false;
        % flag indicating whether adjoint sensitivities should be enabled @type bool
        adjoint = true;
        % flag indicating whether forward sensitivities should be enabled @type bool
        forward = true;
        % default initial time @type double
        t0 = 0;
        % type of wrapper (cvodes/idas) @type string
        wtype = char.empty();
        % number of states @type int
        nx = double.empty();
        % number of original states for second order sensitivities @type int
        nxtrue = 0;
        % number of observables @type int
        ny = double.empty();
        % number of original observables for second order sensitivities @type int
        nytrue = 0;
        % number of parameters @type int
        np = double.empty();
        % number of constants @type int
        nk = double.empty();
        % number of events @type int
        nevent = double.empty();
        % number of event outputs @type int
        nz = double.empty();
        % number of original event outputs for second order sensitivities @type int
        nztrue = double.empty();
        % flag for DAEs @type *int
        id = double.empty();
        % upper Jacobian bandwidth @type int
        ubw = double.empty();
        % lower Jacobian bandwidth @type int
        lbw = double.empty();
        % number of nonzero entries in Jacobian @type int
        nnz = double.empty();
        % dataindexes of sparse Jacobian @type *int
        sparseidx = double.empty();
        % rowindexes of sparse Jacobian @type *int
        rowvals = double.empty();
        % columnindexes of sparse Jacobian @type *int
        colptrs = double.empty();
        % dataindexes of sparse Jacobian @type *int
        sparseidxB = double.empty();
        % rowindexes of sparse Jacobian @type *int
        rowvalsB = double.empty();
        % columnindexes of sparse Jacobian @type *int
        colptrsB = double.empty();
        % cell array of functions to be compiled @type *cell
        funs = cell.empty();
        % optimisation flag for compilation @type string
        coptim = '-O3';
        % default parametrisation @type string
        param = 'lin';
        % path to wrapper
        wrap_path = char.empty();
        % flag to enforce recompilation of the model
        recompile = false;
        % storage for flags determining recompilation of individual
        % functions
        cfun = struct.empty();
        % flag which identifies augmented models 
        %  0 indicates no augmentation
        %  1 indicates augmentation by first order sensitivities (yields
        %  second order sensitivities)
        %  2 indicates augmentation by one linear combination of first
        %  order sensitivities (yields hessian-vector product)
        o2flag = 0;

        % counter that allows enforcing of recompilation of models after
        % code changes
        compver = 10;
    end
    
    properties ( GetAccess = 'public', SetAccess = 'public' )
        % vector that maps outputs to events
        z2event = double.empty();
        % flag indicating whether the model contains spline functions
        splineflag = false;
        % flag indicating whether the model contains min functions
        minflag = false;
        % flag indicating whether the model contains max functions
        maxflag = false;
        % number of derived variables w, w is used for code optimization to reduce the number of frequently occuring
        % expressions @type int
        nw = 0;
        % number of derivatives of derived variables w, dwdx @type int
        ndwdx = 0;
        % number of derivatives of derived variables w, dwdp @type int
        ndwdp = 0;
    end
    
    methods
        function AM = amimodel(symfun,modelname)
            % amimodel initializes the model object based on the provided
            % symfun and modelname
            %
            % Parameters:
            %  symfun: this is the string to the function which generates
            %  the modelstruct. You can also directly pass the struct here @type string
            %  modelname: name of the model @type string
            %
            % Return values:
            %  AM: model definition object
            if(isa(symfun,'char'))
                model = eval(symfun);
            elseif(isa(symfun,'struct'))
                model = symfun;
            else
                error('invalid input symfun')
            end
            
            if(isfield(model,'sym'))
                AM.sym = model.sym;
            else
                error('symbolic definitions missing in struct returned by symfun')
            end
            
            
            
            props = properties(AM);
            
            for j = 1:length(props)
                if(~strcmp(props{j},'sym')) % we already checked for the sym field
                    if(isfield(model,props{j}))
                        AM.(props{j}) = model.(props{j});
                    end
                else
                    AM.makeSyms();
                    AM.nx = length(AM.sym.x);
                    AM.nxtrue = AM.nx;
                    AM.np = length(AM.sym.p);
                    AM.nk = length(AM.sym.k);
                    AM.ny = length(AM.sym.y);
                    AM.nytrue = AM.ny;
                end
            end
            
            AM.modelname = modelname;
            % set path and create folder
            AM.wrap_path=fileparts(fileparts(mfilename('fullpath')));
            if(~exist(fullfile(AM.wrap_path,'models'),'dir'))
                mkdir(fullfile(AM.wrap_path,'models'));
                mkdir(fullfile(AM.wrap_path,'models',AM.modelname));
            else
                if(~exist(fullfile(AM.wrap_path,'models',AM.modelname),'dir'))
                    mkdir(fullfile(AM.wrap_path,'models',AM.modelname))
                end
            end
            AM.makeEvents();
            AM.nz = length([AM.event.z]);
            if(isempty(AM.nztrue))
                AM.nztrue = AM.nz;
            end
            AM.nevent = length(AM.event);
            
            % check whether we have a DAE or ODE
            if(isfield(AM.sym,'M'))
                AM.wtype = 'iw'; % DAE
            else
                AM.wtype = 'cw'; % ODE
            end
        end
        
        function updateRHS(this,xdot)
            % updateRHS updates the private fun property .fun.xdot.sym
            % (right hand side of the differential equation)
            %
            % Parameters:
            %  xdot: new right hand side of the differential equation
            %
            % Return values:
            this.fun.xdot.sym = xdot;
        end
        
        parseModel(this)
        
        generateC(this)
        
        compileC(this)
        
        generateM(this,amimodelo2)
        
        getFun(this,HTable,funstr)
        
        makeEvents(this)
        
        makeSyms(this)
        
        cflag = checkDeps(this,HTable,deps)
        
        HTable = loadOldHashes(this)
        
        modelo2 = augmento2(this)
        
        modelo2vec = augmento2vec(this)
        
    end
end

